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
#include <stdlib.h>
#include <stdbool.h>

#define PI 3.14159265358979323

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

long double
compute_euclidean_norm(Vertex *vt)
{
  long double A = vt->x * vt->x;
  long double B = vt->y * vt->y;
  long double C = vt->z * vt->z;

  return sqrt(A + B + C);
}

long double
compute_dot_product(Vertex *vt1, Vertex *vt2)
{
  long double A = vt1->x * vt2->x;
  long double B = vt1->y * vt2->y;
  long double C = vt1->z * vt2->z;

  return (A + B + C);
}

/* Function for computing the normal of a plane.
 * @param loop is the loop representing a plane.
 * @returns the normal vector
 */
Vertex *
compute_normal(Loop *loop)
{
  Edge *edge1 = NULL, *edge2 = NULL;

  edge1 = loop->edges[0];
  for (size_t i = 0; i < (loop->n); i++) {
    if (edge1->edge_number == loop->edges[i]->edge_number) {
      continue;
    }

    if (compare_vl(edge1->start_vertex, ((Edge *)loop->edges[i])->start_vertex) ||
        compare_vl(edge1->terminate_vertex, ((Edge *)loop->edges[i])->start_vertex) ||
        compare_vl(edge1->terminate_vertex, ((Edge *)loop->edges[i])->terminate_vertex) ||
        compare_vl(edge1->start_vertex, ((Edge *)loop->edges[i])->terminate_vertex)) {
          edge2 = ((Edge *)loop->edges[i]);
          // printf("%d\n", edge2->edge_number);
          break;
    }

  }

  Vertex *vta = compute_line_vector(edge1);
  Vertex *vtb = compute_line_vector(edge2);

  vta = compute_cross_product(vta, vtb);

  return vta;
}

long double
compute_length(Edge *edge)
{
  Vertex *vt = (Vertex *)malloc(sizeof(* vt));

  vt->x = edge->start_vertex->x - edge->terminate_vertex->x;
  vt->y = edge->start_vertex->y - edge->terminate_vertex->y;
  vt->z = edge->start_vertex->z - edge->terminate_vertex->z;

  return compute_euclidean_norm(vt);
}

long double
distance_btwn_planes(Vertex *vt1, Vertex *vt2)
{
  long double num = ((vt1->x) * (vt2->x)) + ((vt1->y) * (vt2->y)) + ((vt1->z) *(vt2->z));
  long double den = compute_euclidean_norm(vt1);

  long double distance = num / den;

  return distance;
}

