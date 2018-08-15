#ifndef FXT_VERTEX_H
#define FXT_VERTEX_H

#include "fxt_types.h"

#define VERTICES_MAX 10000

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
Vertex *vertex_new(long double x, long double y, long double z);
PsectionEntityData *vertexlist_extract(const int pd_pointer, char *ps);

#endif
