#include "ray.h"

t_ray ray_create(t_vec3 origin, t_vec3 direction)
{
    t_ray r = {origin, direction};
    return (r);
}

t_vec3 ray_origin(t_ray r)
{
    return (r.orig);
}

t_vec3 ray_direction(t_ray r)
{
    return (r.dir);
}

t_vec3 ray_at(t_ray r, double t)
{
    return (vec3_add(r.orig, vec3_mul(t, r.dir)));
}
