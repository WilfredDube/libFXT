/**
 * @file fxt_edge.c
 * @author  Wilfred Dube <wilfreddube@gmail.com>
 * @date 13 August 2018
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
 * The Edgelist class represents the iges Edge List entity (Form 1 - 504).
 */
#include "../include/fxt_utils.h"
#include "../include/fxt_edge.h"
#include "../include/fxt_parser.h"

#include <string.h>
#include <stdlib.h>

#define ENTITY_TYPE 504 /**< IGES Entity Type */
#define ENTITY_NAME "Edge List" /**< IGES Entity Name */

/** Create a new Edge object.
* @param model_space_curve_ptr Pointer to the DE of the first model space curve
* @param start_vertex starting vertex of the edge.
* @param terminate_vertex end vertex of the edge.
* @returns Edge object.
*/
static Edge *
edge_new(char *model_space_curve_type, Vertex *start_vertex, Vertex *terminate_vertex)
{
  Edge *edge = (Edge *)malloc(sizeof(* edge));

  edge->model_space_curve_type = model_space_curve_type;
  edge->start_vertex = start_vertex;
  edge->terminate_vertex = terminate_vertex;

  return edge;
}

/** Creates a EdgeList entity object from the pd sections data.
* @param pd_pointer key to uniquely identify each PsectionEntityData object.
* @param ps_data unprocessed pd section data (0 - 64).
* @return pointer to the PsectionEntityData.
*/
EdgeList *
edgelist_extract(char *edgelist_array[])
{
  Edge *edge = NULL;
  EdgeList *edgelist = NULL;

  edgelist = (EdgeList *)malloc(sizeof(* edgelist));

  /* assign the value for N. (N > 0). */
  edgelist->n = utils_to_int(edgelist_array[1]);

  int x = 2, y = 1;
  while(edgelist_array[x] != NULL)
  {
    /* edgelist_array[x] - CURV(1) pointer to the first model_space_curve in DE
    * utils_to_int() - converts CURV pointer to an integer.
    * dsection_get_model_space_curve_type() - gets the curve type of the entity.
    */
    char *curve_type = (char *)dsection_get_model_space_curve_type(utils_to_int(edgelist_array[x]));

    /*
    * edgelist_array[x + 1] - Pointer to the DE of the Vertex List Entity for the start vertex
    * edgelist_array[x + 2] - index value for the vertex in the Vertex List
    * edgelist_array[x + 3] - Pointer to the DE of the Vertex List Entity for the terminate vertex
    * edgelist_array[x + 2] - index value for the vertex in the Vertex List
    */
    Vertex *svt = (Vertex *)dsection_get_vertex(utils_to_int(edgelist_array[x + 1]), utils_to_int(edgelist_array[x + 2]));
    Vertex *tvt = (Vertex *)dsection_get_vertex(utils_to_int(edgelist_array[x + 3]), utils_to_int(edgelist_array[x + 4]));

    edge = edge_new(curve_type, svt, tvt);

    edgelist->edges[y] = (Edge *)malloc(sizeof(Edge *));
    edgelist->edges[y] = edge;

    x += 5; /* Jump to the next edge */
    y++;
  }

  return edgelist;
}
