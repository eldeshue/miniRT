#include <stdio.h>

int main()
{
    float r = 0.0;
    float g = 0.0;
    float b = 0.0;

    int image_witdh = 256;
    int image_height = 256;

    printf("P3\n%d %d\n255\n", image_witdh, image_height);

    for (int j = 0; j < image_height; j++)
    {
        for (int i = 0; i < image_witdh; i++)
        {
            r = (float)i / (image_witdh - 1);
            g = (float)j / (image_height - 1);
            b = 0.25;

            int ir = (int)(255.999 * r);
            int ig = (int)(255.999 * g);
            int ib = (int)(255.999 * b);

            printf("%d %d %d\n", ir, ig, ib);
        }
    }
}