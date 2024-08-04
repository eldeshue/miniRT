#ifndef RAY_H
# define RAY_H

# include "vec3.h"

typedef struct {
    vec3 orig;
    vec3 dir;
} ray;

ray ray_create(vec3 origin, vec3 direction);
vec3 ray_origin(ray r);
vec3 ray_direction(ray r);
vec3 ray_at(ray r, double t);

#endif