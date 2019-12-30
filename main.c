#include <stdio.h>
#include <string.h>
#include "getfiles.h"

int main() {
  int num_files = 0;
  char ** files = getfiles(&num_files);

  int i;
  for (i = 0; i < num_files; i++) {
    printf("%s \n", files[i]);
  }

  return 0;
}
