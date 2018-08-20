#ifndef FXT_UTILS_H
#define FXT_UTILS_H

#include <string.h>
#include <stdlib.h>

int utils_to_int(char *str);
long double utils_to_float(char *str);
long double utils_replace_char(char* str, char find, char replace);
int utils_to_array(char **ret, char *str, char *delim);
char *utils_strsep(char **stringp, const char *delim);

#endif
