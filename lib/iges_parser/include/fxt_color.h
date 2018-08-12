#ifndef FXT_COLOUR_H
#define FXT_COLOUR_H

#include "fxt_types.h"

/* Color - entity 314*/
struct _Color {
  float red;
  float green;
  float blue;
  char* name;
};

PsectionEntityData *color_extract(const int pd_pointer, char *ps, int colornum);
static Color *color_new(float r, float g, float b, char *name);
Color *color_by_number(const unsigned int num);
char *color_name(const unsigned int num);

#endif
