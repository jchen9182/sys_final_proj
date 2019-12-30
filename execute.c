#include <stdio.h>
#include "fileinfo.h"

#define MAX_FILE_LEN 50

void run_file(char *file) {
  char ext[10]; //not aware of any extensions longer than 10 chars
  get_ext(file, ext);
  printf("%s \n", ext);
}
