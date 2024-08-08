#include "sphere.h"

double hit_sphere(t_vec3 center, double radius, t_ray r) {
    t_vec3 oc = vec3_sub(ray_origin(r), center);
    double a = vec3_dot(ray_direction(r), ray_direction(r));
    double b = 2.0 * vec3_dot(oc, ray_direction(r));
    double c = vec3_dot(oc, oc) - radius * radius;
    double discriminant = b * b - 4 * a * c;

    if (discriminant < 0) {
        return -1.0;
    } else {
        return (-b - sqrt(discriminant)) / (2.0 * a);
    }
}