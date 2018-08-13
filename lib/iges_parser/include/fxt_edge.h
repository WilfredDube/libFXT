#ifndef FXT_EDGE_H
#define FXT_EDGE_H

#include "fxt_types.h"

struct _Edge {
  char *model_space_curve_type;
  Vertex *start_vertex;
  Vertex *terminate_vertex;
};

struct _EdgeList {
  int n; /**< Number of edge tuples in list (N > 0)*/
  Edge *edges[]; /**< Array of edges */
};

PsectionEntityData *edgelist_extract(const int pd_pointer, char *ps_data);

#endif
