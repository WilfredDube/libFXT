#ifndef FXT_LOOP_H
#define FXT_LOOP_H

#include "fxt_types.h"

typedef void * List;

struct _Loop {
  int n; /**< Number of loop tuples in list (N > 0)*/
  List edges[]; /**< Array of edges or vertices */
};

PsectionEntityData *loop_extract(const int pd_pointer, char *ps);

#endif
