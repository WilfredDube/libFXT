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
