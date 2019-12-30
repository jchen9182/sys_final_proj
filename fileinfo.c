#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <errno.h>

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
