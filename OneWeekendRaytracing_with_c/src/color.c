#include "color.h"
#include "sphere.h"

void color_write(FILE* out, t_color pixel_color)
{
    int r = (int)(255.999 * pixel_color.e[0]);
    int g = (int)(255.999 * pixel_color.e[1]);
    int b = (int)(255.999 * pixel_color.e[2]);
    fprintf(out, "%d %d %d\n", r, g, b);
}

t_color ray_color(t_ray r)
{
    t_vec3 sphere_center = vec3_create(0, 0, -1);
    double sphere_radius = 0.5;
    
    double t = hit_sphere(sphere_center, sphere_radius, r);
    if (t > 0.0) {
        t_vec3 hit_point = ray_at(r, t);
        t_vec3 normal = vec3_unit(vec3_sub(hit_point, vec3_create(0, 0, -1)));
        return vec3_mul(0.5, vec3_create(normal.e[0] + 1, normal.e[1] + 1, normal.e[2] + 1));
    }

    t_vec3 unit_direction = vec3_unit(ray_direction(r));
    t = 0.5 * (unit_direction.e[1] + 1.0);
    t_color white = vec3_create(1.0, 1.0, 1.0);
    t_color blue = vec3_create(0.5, 0.7, 1.0);
    return vec3_add(vec3_mul(1.0 - t, white), vec3_mul(t, blue));
}
