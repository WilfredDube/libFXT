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

#define ENTITY_TYPE 502
#define ENTITY_NAME "Vertexlist"

/** Create a vertex object
* @param x value in the x-axis
* @param y value in the y-axis
* @param z value in the z-axis
* @returns Vertex object
*/
static Vertex *
vertex_new(float x, float y, float z)
{
  Vertex *vt = (Vertex *)malloc(sizeof(*vt));

  vt->x = x;
  vt->y = y;
  vt->z = z;

  return vt;
}

/** Creates a VertexList entity object from the pd sections data.
* @param pd_pointer key to uniquely identify each PsectionEntityData object.
* @param ps unprocessed pd section data (0 - 64).
* @return pointer to the PsectionEntityData.
*/
PsectionEntityData *
vertexlist_extract(const int pd_pointer, char *ps_data)
{
  int i;
  char *vertexlist_array[PARAM_MAX] = {NULL};
  Vertex *vt = NULL;
  VertexList *vertexlist = NULL;
  PsectionEntityData * psd = NULL;

  utils_to_array(vertexlist_array, ps_data, ",");

  vertexlist = (VertexList *)malloc(sizeof(* vertexlist));

  vertexlist->n = utils_to_int(vertexlist_array[1]);

  int x = 2, y = 0;
  while(vertexlist_array[x] != NULL)
  {
    float x1 = utils_replace_char(vertexlist_array[x], 'D', 'E');
    float y1 = utils_replace_char(vertexlist_array[x + 1], 'D', 'E');
    float z1 = utils_replace_char(vertexlist_array[x + 2], 'D', 'E');

    vt = vertex_new(x1, y1, z1);

    vertexlist->vertices[y] = (Vertex *)malloc(sizeof(Vertex *));
    vertexlist->vertices[y] = vt;

    x += 3; /* Jump to the next vertex */
    y++;
  }

  psd = (PsectionEntityData *)malloc(sizeof(PsectionEntityData*));

  psd = psection_entity_object_new(pd_pointer, ENTITY_TYPE, ENTITY_NAME, vertexlist);

  for (i = 0; i < PARAM_MAX; i++){
    vertexlist_array[i] = NULL;
    free(vertexlist_array[i]);
  }

  return psd;
}
