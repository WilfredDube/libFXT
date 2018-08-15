#ifndef FXT_TRANSMATRIX
#define FXT_TRANSMATRIX

#include "fxt_types.h"

#define COLS 3
#define ROWS 3

struct _TransformationMatrix
{
  long double r_matrix[COLS][ROWS];
  long double t_vector[ROWS];
};

PsectionEntityData *transmatrix_extract(const int pd_pointer, char *ps_data);
Vertex *transmatrix_transform(Vertex *vector, long double r_matrix[][3], long double t_vector[3]);

#endif
