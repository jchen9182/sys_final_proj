#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "fileinfo.h"

#define MAX_FILE_LEN 50

void run_file(char *file) { //for double clicking a file; this function doesn't let the user choose what program to run with
  char ext[10]; //not aware of any extensions longer than 10 chars
  get_ext(file, ext);
  printf("%s \n", ext);

  if (strcmp(ext, ".txt") == 0 || strcmp(ext, ".md") == 0 ||
      strcmp(ext, ".c") == 0 || strcmp(ext, ".h") == 0) {
    pid_t pid = fork();
    if (pid == 0) { //is the child
      execlp("gedit", "gedit", file, NULL);
    }

    return;
  }

  if (strcmp(ext, ".png") == 0 || strcmp(ext, ".jpg") == 0) {
    pid_t pid = fork();
    if (pid == 0) { //is the child
      execlp("eog", "eog", file, NULL);
    }

    return;
  }

  else
    printf("Unrecognized file extension. \n");
}
