#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

//Looking for the properties of a file? Check out fileinfo.c.

int new_file(const char *name) {
  int fd = open(name, O_CREAT | O_EXCL, 0666);
  printf("fd: %d \n", fd);

  if (fd < 0)
    return 0;

  printf("File created! \n");
  return 1;
}

int new_folder(const char *name) {
  int folder = mkdir(name, 0755);

  if (folder < 0)
    return 0;

  printf("Folder created! \n");
  return 1;
}

void remove_thing(const char *thingname) {
  int status = remove(thingname);
  if (status < 0)
    printf("Error %d: %s", errno, strerror(errno));
}
