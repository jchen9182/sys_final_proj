#include "structs.c"

char ** getfiles(int *num_files);

void get_ext(char *filename, char *buff);

void get_props(char *filename, struct fileprops * props);

char * get_properties(char *file_name);

char * get_dir();
