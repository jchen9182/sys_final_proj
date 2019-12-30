#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <errno.h>

#define MAX_FILE_SIZE 50

char ** getfiles(int *num_files) {
  char ** files = malloc(100 * MAX_FILE_SIZE);

  DIR * dir = opendir(".");
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
