#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "fileinfo.h"
#include "execute.h"

int main() {
  int num_files = 0;
  char ** files = getfiles(&num_files);

  int i;
  for (i = 0; i < num_files; i++) {
    printf("[%s] \n", files[i]);
    printf("Extension: ");
    run_file(files[i]);
    struct fileprops prop;
    get_props(files[i], &prop);
    printf("Size: %d bytes \n", prop.size_bytes);
    printf("Permissions: %s \n", prop.perms);

    if (prop.isdir == 0)
      printf("This is a file. \n");
    else
      printf("This is a directory. \n");

    printf("\n");
  }

  return 0;
}
