#include <stdio.h>
#include <string.h>
#include "fileinfo.h"
#include "execute.h"

int main() {
  int num_files = 0;
  char ** files = getfiles(&num_files);

  int i;
  for (i = 0; i < num_files; i++) {
    printf("%s \n", files[i]);
    printf(" >> extension: ");
    run_file(files[i]);
    printf("\n");
  }

  return 0;
}
