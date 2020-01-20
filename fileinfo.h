#include "structs.c"

char ** getfiles(int *num_files);

int file_exists(const char *filename);

void get_ext(const char *filename, char *buff);

void get_props(const char *filename, struct fileprops * props);
