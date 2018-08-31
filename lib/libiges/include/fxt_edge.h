#ifndef FXT_EDGE_H
#define FXT_EDGE_H

#include "fxt_types.h"

#define EDGES_MAX 100000

struct _Edge {
  char *model_space_curve_type;
  Vertex *start_vertex;
  Vertex *terminate_vertex;
};

struct _EdgeList {
  int n; /**< Number of edge tuples in list (N > 0)*/
  Edge *edges[EDGES_MAX]; /**< Array of edges */
};

EdgeList *edgelist_extract(char *ps_edgelist[]);

#endif
