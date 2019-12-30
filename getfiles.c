#include <stdio.h>
#include <string.h>
#include <errno.h>

#define MAX_FILE_SIZE 50

void getfiles(char *files) {
  FILE *fp = popen("ls", "r");
  if (fp == NULL) {
    printf("%s \n", strerror(errno));
    return;
  }

  char file[MAX_FILE_SIZE];
  while (fgets(file, sizeof(file), fp) != NULL)
    strncat(files, file, MAX_FILE_SIZE);

  pclose(fp);
}
