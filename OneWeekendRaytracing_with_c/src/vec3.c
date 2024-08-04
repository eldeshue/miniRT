#include "vec3.h"

vec3 vec3_create(double e0, double e1, double e2)
{
    vec3 v = {{e0, e1, e2}};
    return (v);
}

double vec3_length(vec3 v)
{
    return (sqrt(v.e[0]*v.e[0] + v.e[1]*v.e[1] + v.e[2]*v.e[2]));
}

vec3 vec3_add(vec3 u, vec3 v)
{
    return (vec3_create(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]));
}

vec3 vec3_sub(vec3 u, vec3 v)
{
    return (vec3_create(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]));
}

vec3 vec3_mul(double t, vec3 v)
{
    return (vec3_create(t * v.e[0], t * v.e[1], t * v.e[2]));
}

vec3 vec3_div(vec3 v, double t)
{
    return (vec3_mul(1/t, v));
}

double vec3_dot(vec3 u, vec3 v) 
{
    return (u.e[0] * v.e[0] + u.e[1] * v.e[1] + u.e[2] * v.e[2]);
}

vec3 vec3_cross(vec3 u, vec3 v)
{
    return (vec3_create(
        u.e[1] * v.e[2] - u.e[2] * v.e[1],
        u.e[2] * v.e[0] - u.e[0] * v.e[2],
        u.e[0] * v.e[1] - u.e[1] * v.e[0]
    ));
}

vec3 vec3_unit(vec3 v) {
    return (vec3_div(v, vec3_length(v)));
}
