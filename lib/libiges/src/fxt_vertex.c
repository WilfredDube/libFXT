/**
 * @file fxt_vertex.c
 * @author  Wilfred Dube <wilfreddube@gmail.com>
 * @date 12 August 2018
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
 * The Vertexlist class represents the iges Vertex List entity (Form 1 - 502).
 */
#include "../include/fxt_utils.h"
#include "../include/fxt_vertex.h"
#include "../include/fxt_parser.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define ENTITY_TYPE 502 /**< IGES Entity Type */
#define ENTITY_NAME "Vertex List" /**< IGES Entity Name */

/** Breaks vertex object into x, y, z.
* @param ret_array array to store return values.
* @param vector the vertex break down.
*/
void
vertex_get_coords(long double *ret_array, Vertex *vector)
{
  ret_array[0] = vector->x;
  ret_array[1] = vector->y;
  ret_array[2] = vector->z;
}

/** Create a vertex object
* @param x value in the x-axis
* @param y value in the y-axis
* @param z value in the z-axis
* @returns Vertex object
*/
Vertex *
vertex_new(long double x, long double y, long double z)
{
  Vertex *vt = (Vertex *)malloc(sizeof(*vt));

  vt->x = x;
  vt->y = y;
  vt->z = z;

  return vt;
}

/** Creates a VertexList entity object from the pd sections data.
* @param vertexlist_array array of the Tokenized pd section string.
* @return pointer to the VertexList object.
*/
VertexList *
vertexlist_extract(char *vertexlist_array[])
{
  char *vertexlist_array[PARAM_MAX] = {NULL};
  Vertex *vt = NULL;
  VertexList *vertexlist = NULL;
  PsectionEntityData * psd = NULL;

  utils_to_array(vertexlist_array, ps_data, DELIMITER);

  vertexlist = (VertexList *)malloc(sizeof(VertexList));

  vertexlist->n = utils_to_int(vertexlist_array[1]);
  printf("%s\n", vertexlist_array[0]);

  size_t y, x;
  for (y = 0, x = 2; y < vertexlist->n; y++, x+=3)
  {
    long double x1 = utils_replace_char(vertexlist_array[x], 'D', 'E');
    long double y1 = utils_replace_char(vertexlist_array[x + 1], 'D', 'E');
    long double z1 = utils_replace_char(vertexlist_array[x + 2], 'D', 'E');

    printf("%ld: %Lg %Lg %Lg\n", x, x1, y1, z1);
    vt = vertex_new(x1, y1, z1);

    vertexlist->vertices[y] = malloc(sizeof(Vertex));
    vertexlist->vertices[y] = vt;
  }

  psd = (PsectionEntityData *)malloc(sizeof(PsectionEntityData*));

  // psd = psection_entity_object_new(pd_pointer, ENTITY_TYPE, ENTITY_NAME, vertexlist);

  return psd;
}
