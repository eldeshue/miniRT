#include "vec3.h"

typedef vec3 color;

void write_color(FILE* out, color pixel_color) {
    int r = (int)(255.999 * pixel_color.e[0]);
    int g = (int)(255.999 * pixel_color.e[1]);
    int b = (int)(255.999 * pixel_color.e[2]);
    fprintf(out, "%d %d %d\n", r, g, b);
}
