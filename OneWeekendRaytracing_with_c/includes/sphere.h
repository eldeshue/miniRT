#ifndef SPHERE_H
# define SPHERE_H

# include "vec3.h"
# include "ray.h"

double hit_sphere(t_vec3 center, double radius, t_ray r);

#endif