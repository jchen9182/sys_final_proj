#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define MAX_FILE_SIZE 50

char ** getfiles(int *num_files) {
  char ** files = malloc(5000); //space to fit all files
  FILE *fp = popen("ls", "r");
  if (fp == NULL) {
    printf("%s \n", strerror(errno));
    return NULL;
  }

  char file[MAX_FILE_SIZE];
  printf("Printing the 2D array in the while loop: \n");
  while (fgets(file, sizeof(file), fp) != NULL) {
    char *curr = file;
    files[*num_files] = strsep(&curr, "\n");
    printf("%s \n", files[*num_files]);
    (*num_files)++;
  }

  printf("\nPrinting the 2D array one by one outside the while loop: \n");
  printf("%s \n", files[0]);
  printf("%s \n", files[1]);
  printf("%s \n", files[2]);
  printf("%s \n", files[3]);
  printf("%s \n", files[4]);
  printf("%s \n", files[5]);
  printf("%s \n", files[6]);
  printf("%s \n", files[7]);
  printf("%s \n", files[8]);

  files[*num_files] = NULL;
  pclose(fp);
  return files;
}
