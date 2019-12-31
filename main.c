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
    printf("%s \n", files[i]);
    printf(" >> extension: ");
    run_file(files[i]);
    struct fileprops prop;
    get_props(files[i], &prop);
    printf("\n");
    printf("%d bytes \n", prop.size_bytes);
    printf("%s \n", prop.perms);
    printf("\n");
  }

  return 0;
}
