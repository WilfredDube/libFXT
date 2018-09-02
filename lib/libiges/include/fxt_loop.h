#ifndef FXT_LOOP_H
#define FXT_LOOP_H

#include "fxt_types.h"

#define LOOP_MAX 10000

typedef void * List;

struct _Loop {
  int n; /**< Number of loop tuples in list (N > 0)*/
  List edges[LOOP_MAX]; /**< Array of edges or vertices */
};

Loop *loop_extract(char *loop_array[]);
void print_num(Loop *lp);

#endif
