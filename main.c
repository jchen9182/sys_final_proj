#include <stdio.h>
#include "getfiles.h"

int main() {
  char files[10000];
  getfiles(files);
  printf("%s", files);

  return 0;
}
