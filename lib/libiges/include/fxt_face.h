#ifndef FXT_FACE_H
#define FXT_FACE_H

#include "fxt_types.h"

#include <stdbool.h>

struct _Face {
  char *face_id; /* value = F# e.g F1, F2, F78. */
  int surface; /* change actual surface value later. */
  int n; /**< Number of loops (N > 0)*/
  bool outer_flag;
  Loop *inner_loop[LOOPS_MAX]; /**< Array of loop. */
  Loop *outer_loop[LOOPS_MAX];
};

PsectionEntityData *loop_extract(const int pd_pointer, char *ps);

#endif
