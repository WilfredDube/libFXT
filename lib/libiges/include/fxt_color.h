#ifndef FXT_COLOUR_H
#define FXT_COLOUR_H

#include "fxt_types.h"

/* Color - entity 314*/
struct _Color {
  long double red;
  long double green;
  long double blue;
  char* name;
};

PsectionEntityData *color_extract(const int pd_pointer, char *ps, int colornum);
Color *color_by_number(const unsigned int num);
char *color_name(const unsigned int num);

#endif
