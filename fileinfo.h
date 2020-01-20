#include "structs.c"

char ** getfiles(int *num_files);

int file_exists(const char *filename);

void get_ext(char *filename, char *buff);

void get_props(char *filename, struct fileprops * props);
