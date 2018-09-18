
#ifndef FXT_MATH_H
#define  FXT_MATH_H

#include "fxt_types.h"
#include <stdbool.h>

Vertex *compute_normal(Loop *loop);
long double compute_length(Edge *edge);
long double compute_bend_length(Edge *edge);
long double compute_angle(Vertex *norm1, Vertex *norm2);
bool issideplane(Loop *edge_loop, long double thickness);
long double compute_thickness(Loop *loop);
bool is_parallel(Vertex *norm1, Vertex *norm2);
bool is_distance_thickness(Face *fc1, Face *fc2);
Loop *central_face_generation(Face *fc);
long double compute_distance_btw_planes(Face *fc1, Face *fc2);
long double compute_distance_btw_2_points(Vertex *norm1, Vertex *norm2);
long double compute_distance_btw_plane_points(Face *fc1, Face *fc2);
long double compute_gradient(Edge *edge);
long double compute_bending_force(long double *bendlength, long double thickness, int unit, long double tensile_strength);
void compute_plane_equation(Face *face);

#endif
