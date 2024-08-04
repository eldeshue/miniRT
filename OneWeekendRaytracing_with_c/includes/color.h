#ifndef COLOR_H
# define COLOR_H

# include "vec3.h"
# include "ray.h"

typedef t_vec3 t_color;

void color_write(FILE* out, t_color pixel_color);
t_color ray_color(t_ray r);

#endif