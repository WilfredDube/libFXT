#ifndef FXT_VERTEX_H
#define FXT_VERTEX_H

#include "fxt_types.h"

#define VERTICES_MAX 10000

struct _Point {
  int x;
  int y;
  int z;
};

struct _VertexList {
  int n; /**< Number of vertex tuples in list (N > 0)*/
  Vertex *vertices[VERTICES_MAX]; /**< Array of vertices */
};

PsectionEntityData *vertexlist_extract(const int pd_pointer, char *ps);

#endif
