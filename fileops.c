#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

//Looking for the properties of a file? Check out fileinfo.c.

void new_file() {
  int fd = open("Untitled Document", O_CREAT | O_EXCL, 0666);
  printf("fd: %d \n", fd);

  if (fd < 0)
    fd = open("Untitled Document 2", O_CREAT, 0666);

  printf("File created! \n");
}

void new_folder() {
  int folder = mkdir("New Folder", 0755);

  if (folder < 0)
    printf("Error %d: %s", errno, strerror(errno));
}

void rename_thing(char *oldname, char *newname) {
  int status = rename(oldname, newname);
  if (status < 0)
    printf("Error %d: %s", errno, strerror(errno));
}

void remove_thing(char *thingname) {
  int status = remove(thingname);
  if (status < 0)
    printf("Error %d: %s", errno, strerror(errno));
}
