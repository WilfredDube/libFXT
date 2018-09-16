/**
 * @file fxt_rbscurve.c
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
 * The RBSCurve class represents the iges Rational B-Spline Curve entity (126).
 */
#include "../include/fxt_utils.h"
#include "../include/fxt_rbscurve.h"
#include "../include/fxt_parser.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define ENTITY_TYPE 126 /**< IGES Entity Type */
#define ENTITY_NAME "Rational B-Spline Curve" /**< IGES Entity Name */

RBSCurve *
rbscurve_extract(char *ps_rbsc[])
{
  RBSCurve *rbscurve = NULL;

  rbscurve = (RBSCurve *)malloc(sizeof(RBSCurve));

  rbscurve->k = utils_to_int(ps_rbsc[j]);
  int K = rbscurve->k;

  rbscurve->m = utils_to_int(ps_rbsc[j + 1]);
  int M = rbscurve->m;

  rbscurve->PROP1 = utils_to_int(ps_rbsc[j + 2]);
  rbscurve->PROP2 = utils_to_int(ps_rbsc[j + 3]);
  rbscurve->PROP3 = utils_to_int(ps_rbsc[j + 4]);
  rbscurve->PROP4 = utils_to_int(ps_rbsc[j + 5]);

  int N = 1 + K - M;
  int A = N + 2 * M;

  int knotstart = j + 6;
  int knotend = knotstart + A;


  return rbscurve;
}
