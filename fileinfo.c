#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include "structs.c"

#define MAX_FILE_LEN 50

char ** getfiles(int *num_files) {
  char ** files = malloc(100 * sizeof(char *)); //can be any size but I doubt we'll be testing in a folder w/ > 100 files/folders
  DIR * dir = opendir("."); //current working directory for now as a proof of concept
  struct dirent * info = readdir(dir);
  while (info != NULL) {
    if (info -> d_name[0] != '.') { //conditional gets rid of hidden files/folders
      files[*num_files] = (char *)malloc(MAX_FILE_LEN);
      strncpy(files[*num_files], info -> d_name, MAX_FILE_LEN);
      (*num_files)++;
    }

    info = readdir(dir); //move on to the next entry
  }

  files[*num_files] = NULL; //end the array in case there is extra stuff stored from earlier runs of this function
  closedir(dir);
  return files;
}

void get_ext(char *filename, char *buff) {
  int i = strlen(filename) - 1;
  while (i >= 0) { //loop backwards to find the '.'; not aware of a backwards strsep and this is easy anyway
    if (filename[i] == '.') {
      strncpy(buff, filename + i, 10); //filename + i makes it so that strncpy only starts copying from the period onwards
      return; //exit the loop since the extension has been found
    }

    i--;
  }

	strcpy(buff, "\0"); //period not found; make the extension a null-ended string which gets returned
}

void get_props(char *filename, struct fileprops * props) {
  struct stat metadata;
  stat(filename, &metadata);

  //edit every individual byte of props -> perms string in the file properties struct
  props -> perms[0] = (metadata.st_mode & S_IRUSR) ? 'r' : '-';
  props -> perms[1] = (metadata.st_mode & S_IWUSR) ? 'w' : '-';
  props -> perms[2] = (metadata.st_mode & S_IXUSR) ? 'x' : '-';
  props -> perms[3] = (metadata.st_mode & S_IRGRP) ? 'r' : '-';
  props -> perms[4] = (metadata.st_mode & S_IWGRP) ? 'w' : '-';
  props -> perms[5] = (metadata.st_mode & S_IXGRP) ? 'x' : '-';
  props -> perms[6] = (metadata.st_mode & S_IROTH) ? 'r' : '-';
  props -> perms[7] = (metadata.st_mode & S_IWOTH) ? 'w' : '-';
  props -> perms[8] = (metadata.st_mode & S_IXOTH) ? 'x' : '-';
  props -> perms[9] = '\0'; //for some reason there's extra bytes to the right of the S_IXOTH byte even though the string is 9 large, whatever this fixes it

  props -> size_bytes = metadata.st_size;

  props -> isdir = (S_ISDIR(metadata.st_mode)) ? 1 : 0;
}

char * get_properties(char *file_name) {
  char * properties = malloc(sizeof(char) * 500);
  struct fileprops prop;
  char * size = malloc(sizeof(char) * 100);
  get_props(file_name, &prop);
  strcat(properties, "File Name: ");
  strcat(properties, file_name);
  strcat(properties, "\n");
  strcat(properties, "Size: ");
  sprintf(size, "%d", prop.size_bytes);
  strcat(properties, size);
  strcat(properties, " bytes \n");
  strcat(properties, "Permissions: ");
  strcat(properties, prop.perms);
  strcat(properties, "\n");
  if (prop.isdir == 0) {
    strcat(properties, "Type: file \nExtension: ");
    char ext[10];
	  get_ext(file_name, ext);
    strcat(properties, ext);
    strcat(properties, "\n");
  }

  strcat(properties, "Type: directory \n");
  return properties;
}

char * get_dir() {
  char * wd;
  wd = malloc(sizeof(char) * 100);
  getcwd(wd, 100);
  return wd;
}
