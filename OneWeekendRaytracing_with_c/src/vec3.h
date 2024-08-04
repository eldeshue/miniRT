#ifndef VEC3_H
# define VEC3_H

#include <math.h>
#include <stdio.h>

typedef struct {
    double e[3];
} vec3;

vec3 vec3_create(double e0, double e1, double e2);
double vec3_length(vec3 v);
vec3 vec3_add(vec3 u, vec3 v);
vec3 vec3_sub(vec3 u, vec3 v);
vec3 vec3_mul(double t, vec3 v);
vec3 vec3_div(vec3 v, double t);
double vec3_dot(vec3 u, vec3 v);
vec3 vec3_cross(vec3 u, vec3 v);
vec3 vec3_unit(vec3 v);

#endif