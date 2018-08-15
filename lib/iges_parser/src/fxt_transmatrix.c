/**
 * @file fxt_transmatrix.c
 * @author  Wilfred Dube <wilfreddube@gmail.com>
 * @date 15 August 2018
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
 * The Transmatrix class represents the iges transformation Matrix entity (124).
 */
#include "../include/fxt_utils.h"
#include "../include/fxt_vertex.h"
#include "../include/fxt_transmatrix.h"
#include "../include/fxt_parser.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#define ENTITY_TYPE 124 /**< IGES Entity Type */
#define ENTITY_NAME "Transformation Matrix" /**< IGES Entity Name */
#define TMX_PARAMS 13 /**< Number of parameter in the pd section. */

/** Transforms three-row column vectors by means of a matrix multiplication and then a vector addition.
* @param vector the vertex to be transformed.
* @param r_matrix 3D Matrix.
* @param t_vector column vector.
* @returns Vertex object resulting from the transformation.
*/
Vertex *
transmatrix_transform(Vertex *vector, long double r_matrix[][3], long double t_vector[3])
{
  long double arr[3] = {0};

  vertex_get_coords(arr, vector);

  long double x = arr[0];
  long double y = arr[1];
  long double z = arr[2];

  /* Multiply the vertex by the matrix. */
  x = (r_matrix[0][0] * x) + (r_matrix[0][1] * x) + (r_matrix[0][2] * x);
  y = (r_matrix[1][0] * y) + (r_matrix[1][1] * y) + (r_matrix[1][2] * y);
  z = (r_matrix[2][0] * z) + (r_matrix[2][1] * z) + (r_matrix[2][2] * z);

  /* Add the column vector. */
  x = x + t_vector[0];
  y = y + t_vector[1];
  z = z + t_vector[2];

  vector = (Vertex *)vertex_new(x, y, z);

  return vector;
}

/** Creates a TransformationMatrix entity object from the pd sections data.
* @param pd_pointer key to uniquely identify each PsectionEntityData object.
* @param ps_data unprocessed pd section data (0 - 64).
* @return pointer to the PsectionEntityData.
*/
PsectionEntityData *
transmatrix_extract(const int pd_pointer, char *ps_data)
{
  char *tmx_array[TMX_PARAMS] = {NULL};
  TransformationMatrix *tmx = NULL;
  PsectionEntityData *psd = NULL;

  utils_to_array(tmx_array, ps_data, DELIMITER);

  tmx = (TransformationMatrix *)malloc(sizeof(TransformationMatrix));

  for (size_t i = 1, v = 0, m = 0; i < TMX_PARAMS; i++, v++, m++) {
    for (size_t j = 0; j < 3; j++) {
      if ((i % 4) != 0) {
        tmx->r_matrix[m][j] = utils_replace_char(tmx_array[i], 'D', 'E');
        i++;
      }
    }

    if ((i % 4) == 0) {
      tmx->t_vector[v] = utils_replace_char(tmx_array[i], 'D', 'E');
    }
  }

  psd = (PsectionEntityData *)malloc(sizeof(PsectionEntityData*));

  // psd = psection_entity_object_new(pd_pointer, ENTITY_TYPE, ENTITY_NAME, tmx);

  return psd;
}
