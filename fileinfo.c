#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include "structs.c"

#define MAX_FILE_LEN 50

char ** getfiles(int *num_files) {
  char ** files = malloc(100 * MAX_FILE_LEN);

  DIR * dir = opendir("."); //current working directory for now as a proof of concept
  struct dirent * info = readdir(dir);
  while (info != NULL) {
    if (info -> d_name[0] != '.') { //conditional gets rid of hidden files/folders
      files[*num_files] = info -> d_name;
      (*num_files)++;
    }

    info = readdir(dir); //move on to the next entry
  }

  files[*num_files] = NULL;
  closedir(dir);
  return files;
}

void get_ext(char *filename, char *buff) {
  int i = strlen(filename) - 1;
  while (i >= 0) {
    if (filename[i] == '.') {
      strncpy(buff, filename + i, 10);
      return;
    }

    i--;
  }

  strcpy(buff, "\0");
}

void get_props(char *filename, struct fileprops * props) {
  struct stat metadata;
  stat(filename, &metadata);

  props -> perms[0] = (metadata.st_mode & S_IRUSR) ? 'r' : '-';
  props -> perms[1] = (metadata.st_mode & S_IWUSR) ? 'w' : '-';
  props -> perms[2] = (metadata.st_mode & S_IXUSR) ? 'x' : '-';
  props -> perms[3] = (metadata.st_mode & S_IRGRP) ? 'r' : '-';
  props -> perms[4] = (metadata.st_mode & S_IWGRP) ? 'w' : '-';
  props -> perms[5] = (metadata.st_mode & S_IXGRP) ? 'x' : '-';
  props -> perms[6] = (metadata.st_mode & S_IROTH) ? 'r' : '-';
  props -> perms[7] = (metadata.st_mode & S_IWOTH) ? 'w' : '-';
  props -> perms[8] = (metadata.st_mode & S_IXOTH) ? 'x' : '-';
  props -> perms[9] = '\0';

  props -> size_bytes = metadata.st_size;
}
