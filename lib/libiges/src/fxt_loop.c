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
#include "../include/fxt_math.h"

#include <string.h>
#include <stdlib.h>

#define ENTITY_TYPE 508 /**< IGES Entity Type */
#define ENTITY_NAME "Loop" /**< IGES Entity Name */


void print_num(Loop *lp) {
  printf("%d\n", lp->n);
}

/** Creates a loop entity object from the pd sections data.
* @param pd_pointer key to uniquely identify each PsectionEntityData object.
* @param ps_data unprocessed pd section data (0 - 64).
* @return pointer to the PsectionEntityData.
*/
Loop *
loop_extract(char *loop_array[])
{
  int x = 2, y = 0, k, type;
  Loop *loop = NULL;

  loop = (Loop *) malloc(sizeof(* loop));
  loop->n = utils_to_int(loop_array[1]);
  loop->loop_type = -1;

  while (loop_array[x] != NULL){

    if ((y + 1) > loop->n) {
      break;
    }

    type = utils_to_int(loop_array[x]); /* type */
    // k = utils_to_int(loop_array[x + 4]);

    // printf("Values : %d . %d . %d\n", type, utils_to_int(loop_array[x + 1]), utils_to_int(loop_array[x + 2]) );
    if (type == 0){
      loop->edges[y] = dsection_get_edge(utils_to_int(loop_array[x + 1]), utils_to_int(loop_array[x + 2]));
      // printf("%d\n", y);
    } else {
      // printf("vt\n");
      loop->vertices[y] = dsection_get_vertex(utils_to_int(loop_array[x + 1]), utils_to_int(loop_array[x + 2]));
    }

    if (k != 0) {
      /* code */
      // x = 9 + k;
    }

    x += 5;
    ++y;
  }

  int edge_count = 1;
  for (size_t i = 0; i < loop->n; i++) {
    if (loop->edges[i]->edge_type == ARC) {
      loop->loop_type = CURVED_SURRFACE;
      break;
    } else {
      ++edge_count;
    }

    if ((edge_count == loop->n) && (loop->loop_type == -1)) {
      loop->loop_type = PLANAR_SURFACE;
      // printf("%d\n", edge_count);
      break;
    }
  }


  vt = NULL;
  free(vt);

  return loop;
}
