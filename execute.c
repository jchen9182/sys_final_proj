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
      //tried using a system call of "xdg-open" to open default applications, ended in a fork bomb lol
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

void back() {
  if (chdir("..") < 0) {
    printf("chdir() error: %s\n",strerror(errno));
  }
}

void enter_directory(char *directory) {
  if (chdir(directory) < 0) {
    printf("chdir() error: %s\n",strerror(errno));
  }
}

void double_click(char *file_name) {
  struct fileprops prop;
  get_props(file_name, &prop);
  if (prop.isdir == 0)
    run_file(file_name);
  else
    enter_directory(file_name);
}
