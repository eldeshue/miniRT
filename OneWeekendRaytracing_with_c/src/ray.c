#include "ray.h"

ray ray_create(vec3 origin, vec3 direction)
{
    ray r = {origin, direction};
    return (r);
}

vec3 ray_origin(ray r)
{
    return (r.orig);
}

vec3 ray_direction(ray r)
{
    return (r.dir);
}

vec3 ray_at(ray r, double t)
{
    return (vec3_add(r.orig, vec3_mul(t, r.dir)));
}
