#ifndef FXT_FACE_H
#define FXT_FACE_H

#include "fxt_types.h"

#include <stdbool.h>

struct _Face {
  char face_id[5]; /* value = F# e.g F1, F2, F78. */
  int surface_ptr; /* change actual surface value later. */
  int n; /**< Number of loops (N > 0)*/
  bool outer_flag;
  Loop *inner_loop[LOOPS_MAX]; /**< Array of loop. */
  Loop *outer_loop[LOOPS_MAX];
};

Face *face_extract(char *face_array[]);

#endif
