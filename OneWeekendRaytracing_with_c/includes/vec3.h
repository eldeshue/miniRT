#ifndef VEC3_H
# define VEC3_H

#include <math.h>
#include <stdio.h>

typedef int t_bool;

typedef struct s_vec3{
    double e[3];
} t_vec3;

t_vec3 vec3_create(double e0, double e1, double e2);
double vec3_length(t_vec3 v);
double vec3_length_squared(t_vec3 v);
t_vec3 vec3_add(t_vec3 u, t_vec3 v);
t_vec3 vec3_sub(t_vec3 u, t_vec3 v);
t_vec3 vec3_mul(double t, t_vec3 v);
t_vec3 vec3_div(t_vec3 v, double t);
double vec3_dot(t_vec3 u, t_vec3 v);
t_vec3 vec3_cross(t_vec3 u, t_vec3 v);
t_vec3 vec3_unit(t_vec3 v);

#endif