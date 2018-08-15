/**
 * @file fxt_loop.c
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
 * The Loop class represents the iges Loop entity (Form 1 - 508).
 */
#include "../include/fxt_utils.h"
#include "../include/fxt_loop.h"
#include "../include/fxt_parser.h"

#include <string.h>
#include <stdlib.h>

#define ENTITY_TYPE 508 /**< IGES Entity Type */
#define ENTITY_NAME "Loop" /**< IGES Entity Name */

/** Creates a loop entity object from the pd sections data.
* @param pd_pointer key to uniquely identify each PsectionEntityData object.
* @param ps_data unprocessed pd section data (0 - 64).
* @return pointer to the PsectionEntityData.
*/
PsectionEntityData *
Loop_extract(const int pd_pointer, char *ps_data)
{
  int x = 2, y = 0, k, type;
  char *edge_array[PARAM_MAX] = { NULL };
  Loop *loop = NULL;
  PsectionEntityData * psd = NULL;

  utils_to_array(edge_array, ps_data, DELIMITER);

  loop = (Loop *) malloc(sizeof(* loop));
  loop->n = utils_to_int(edge_array[1]);

  while (edge_array[x] != NULL){
    type = utils_to_int(edge_array[x]); /* type */\
    k = utils_to_int(edge_array[x + 4]);

    if (type == 0){
      loop->edges[y] = dsection_get_edge(utils_to_int(edge_array[x + 1]), utils_to_int(edge_array[x + 2]));
    } else {
      loop->edges[y] = dsection_get_vertex(utils_to_int(edge_array[x + 1]), utils_to_int(edge_array[x + 2]));
    }
    x = 9 + k;
  }

  psd = (PsectionEntityData *)malloc(sizeof(PsectionEntityData *));

  psd = psection_entity_object_new(pd_pointer, ENTITY_TYPE, ENTITY_NAME, loop);

  return psd;
}
