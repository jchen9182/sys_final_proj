#include <stdio.h>
#include <string.h>
#include "getfiles.h"

int main() {
  int num_files = 0;
  char ** files = getfiles(&num_files);

  int i;
  //printf("Looping through 2D array in main: \n");
  //for (i = 0; i < num_files; i++) {
    //printf("%s \n", files[i]);
  //}

  return 0;
}
