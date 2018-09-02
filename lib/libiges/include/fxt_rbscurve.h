#ifndef FXT_RBSCURVE_H
#define FXT_RBSCURVE_H

#include "fxt_types.h"

#define RBSCURVE_MAX 100000

struct _RBSCurve {
  int k;
  int m;
  int PROP1;
  int PROP2;
  int PROP3;
  int PROP4;
  long double knot_sequence[];
  long double weights[];
  long double control_points[];
  long double start_parameter;
  long double end_parameter;
  long double xnorm; /* Unit normal x (if planar) */
  long double ynorm; /* Unit normal y (if planar) */
  long double znorm; /* Unit normal z (if planar) */
};

RBSCurve *rbscurve_extract(char *ps_edgelist[]);

#endif
