/**
 * @file fxt_face.c
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
 * The Face class represents the iges color definition entity (510).
 */

#include "../include/fxt_utils.h"
#include "../include/fxt_face.h"
#include "../include/fxt_parser.h"

#include <stdio.h>

#define ENTITY_TYPE 510 /**< IGES Entity Type */
#define ENTITY_NAME "Face" /**< IGES Entity Name */

static unsigned face_id = 1;

/** Creates a face entity object from the pd sections data.
* @param pd_pointer key to uniquely identify each PsectionEntityData object.
* @param ps_data unprocessed pd section data (0 - 64).
* @return pointer to the PsectionEntityData.
*/
PsectionEntityData *
face_extract(int pd_pointer, char * ps_data)
{
  Face *face = NULL;
  char *face_array[PARAM_MAX] = {NULL};
  PsectionEntityData *psd = NULL;

  utils_to_array(face_array, ps_data, ",");

  face = (Face *)malloc(sizeof(* face));

  sprintf(face->face_id, "F%d", face_id);

  face->surface = utils_to_int(face_array[1]);
  face->n = utils_to_int(face_array[2]);
  face->outer_flag = (bool)utils_to_int(face_array[3]);

  int N = face->n;
  for (int x = 4, y =0; (x - 4) < N; x++, y++){
     face->inner_loop[y]= dsection_get_loop(utils_to_int(face_array[x]));
  }

  psd = (PsectionEntityData *)malloc(sizeof(PsectionEntityData *));
  psd = psection_entity_object_new(pd_pointer, ENTITY_TYPE, ENTITY_NAME, face);

  return psd;
}
