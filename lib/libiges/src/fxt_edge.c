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
#include "../include/fxt_vertex.h"
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
edge_new(int model_space_curve_type, int edge_type, int edge_number, Vertex *start_vertex, Vertex *terminate_vertex)
{
  Edge *edge = (Edge *)malloc(sizeof(* edge));

  edge->model_space_curve_type = model_space_curve_type;
  edge->edge_number = edge_number;
  edge->edge_type = edge_type;
  edge->start_vertex = start_vertex;
  edge->terminate_vertex = terminate_vertex;
  // printf("%d\n", edge->model_space_curve_type);

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

  int x = 2, y = 0;
  while(edgelist_array[x] != NULL)
  {
    if(y == edgelist->n){
      // printf("EXIT\n");
      break;
    }

    /* edgelist_array[x] - CURV(1) pointer to the first model_space_curve in DE
    * utils_to_int() - converts CURV pointer to an integer.
    * dsection_get_model_space_curve_type() - gets the curve type of the entity.
    */

    int curve_type = dsection_get_model_space_curve_type(utils_to_int(edgelist_array[x]));
    /*
    * edgelist_array[x + 1] - Pointer to the DE of the Vertex List Entity for the start vertex
    * edgelist_array[x + 2] - index value for the vertex in the Vertex List
    * edgelist_array[x + 3] - Pointer to the DE of the Vertex List Entity for the terminate vertex
    * edgelist_array[x + 2] - index value for the vertex in the Vertex List
    */
    Vertex *svt = (Vertex *)dsection_get_vertex(utils_to_int(edgelist_array[x + 1]), utils_to_int(edgelist_array[x + 2]));
    Vertex *tvt = (Vertex *)dsection_get_vertex(utils_to_int(edgelist_array[x + 3]), utils_to_int(edgelist_array[x + 4]));

    int edge_type;
    if (dsection_get_edge_type(utils_to_int(edgelist_array[x]))) {
      edge_type = LINE;
    } else {
      edge_type = ARC;
    }
    // printf("%d\n", edge_type);

    if (svt == NULL) {
      // printf("NULL!\n" );
    }
    // printf("Start %d: %Lg, %Lg, %Lg\n", y, tvt->x, tvt->y, tvt->z);

    edge = edge_new(curve_type, edge_type, (y + 1), svt, tvt);

    edgelist->edges[y] = (Edge *)malloc(sizeof(Edge *));
    edgelist->edges[y] = edge;

    // printf("%Lg\n", edgelist->edges[0]->start_vertex->x);
    x += 5; /* Jump to the next edge */
    y++;
  }

  return edgelist;
}
