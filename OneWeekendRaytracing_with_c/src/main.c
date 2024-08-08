#include "color.h"
#include "ray.h"
#include "vec3.h"

#include <stdio.h>

int main()
{
    // 이미지 설정
    double aspect_ratio = 16.0 / 9.0;
    int image_width = 400;
    int image_height = (int)(image_width / aspect_ratio);

    // 카메라 설정
    double viewport_height = 2.0;
    double viewport_width = aspect_ratio * viewport_height;
    double focal_length = 1.0;

    t_vec3 origin = vec3_create(0, 0, 0);
    t_vec3 horizontal = vec3_create(viewport_width, 0, 0);
    t_vec3 vertical = vec3_create(0, viewport_height, 0);
    t_vec3 lower_left_corner = vec3_sub(vec3_sub(vec3_sub(origin, vec3_div(horizontal, 2)), vec3_div(vertical, 2)), vec3_create(0, 0, focal_length));

    // 렌더링
    FILE *image_file = fopen("image.ppm", "w");
    fprintf(image_file, "P3\n%d %d\n255\n", image_width, image_height);

    for (int j = image_height - 1; j >= 0; --j) {
        fprintf(stderr, "\r남은 스캔라인: %d ", j);
        fflush(stderr);
        for (int i = 0; i < image_width; ++i) {
            double u = (double)i / (image_width - 1);
            double v = (double)j / (image_height - 1);
            t_vec3 direction = vec3_add(vec3_add(lower_left_corner, vec3_mul(u, horizontal)), vec3_mul(v, vertical));
            direction = vec3_sub(direction, origin);
            t_ray r = ray_create(origin, direction);
            t_color pixel_color = ray_color(r);
            color_write(image_file, pixel_color);
        }
    }

    fprintf(stderr, "\n완료.\n");
    fclose(image_file);
    return 0;
}
