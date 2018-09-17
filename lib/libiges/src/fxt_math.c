/**
 * @file fxt_math.c
 * @author  Wilfred Dube <wilfreddube@gmail.com>
 * @date 16 August 2018
 * @version 1.0
 *
 * @section LICENSE
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details at
 * https://www.gnu.org/copyleft/gpl.html
 *
 * @section DESCRIPTION
 *
 * The Math cpmputation class for all calculations.
 */
#include "../include/fxt_math.h"
#include "../include/fxt_parser.h"
#include "../include/fxt_vertex.h"
#include "../include/fxt_edge.h"
#include "../include/fxt_loop.h"
#include "../include/fxt_types.h"
#include <math.h>
#include <stdbool.h>

bool compare_vl(Vertex *v1, Vertex *v2)
{
  bool truth = false;

  if (v1->x == v2->x && v1->y == v2->y && v1->z == v2->z) {
    truth = true;
  }

  return truth;
}

Vertex *
compute_cross_product(Vertex *a, Vertex *b)
{
  Vertex *normal = (Vertex *)malloc(sizeof(* normal));

  normal->x = (a->y * b->z) - (a->z * b->y);
  normal->y = - ((a->x * b->z) - (a->z * b->x));
  normal->z = (a->x * b->y) - (a->y * b->x);

  return normal;
}

Vertex *
compute_line_vector(Edge *edge)
{
  Vertex *vt = (Vertex *)malloc(sizeof(* vt));

  vt->x = edge->start_vertex->x - edge->terminate_vertex->x;
  vt->y = edge->start_vertex->y - edge->terminate_vertex->y;
  vt->z = edge->start_vertex->z - edge->terminate_vertex->z;

  return vt;
}

/* Function for computing the normal of a plane.
 * @param loop is the loop representing a plane.
 * @returns the normal vector
 */
Vertex *compute_normal(Loop *loop){
  // printf("LOOP = %d\n", (int)((Edge *)loop->edges[0])->model_space_curve_type);
  // Vertex *vt_s = get_start_vertex(((Edge *)loop->edges[0]));
  // printf("%Lg\n", ((Edge *)loop->edges[0])->start_vertex->x);
  // printf("%p\n", loop->edges);

  return NULL;
}
