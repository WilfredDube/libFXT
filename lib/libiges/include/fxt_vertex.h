#ifndef FXT_VERTEX_H
#define FXT_VERTEX_H

#include "fxt_types.h"

#define VERTICES_MAX 100000

struct _Point {
  long double x;
  long double y;
  long double z;
};

struct _VertexList {
  int n; /**< Number of vertex tuples in list (N > 0)*/
  Vertex *vertices[VERTICES_MAX]; /**< Array of vertices */
};

void vertex_get_coords(long double *arr, Vertex *vector);
VertexList *vertexlist_extract(char *vertexlist_array[]);

#endif
