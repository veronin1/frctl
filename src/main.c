#include <complex.h>
#include <stdio.h>

const int height = 800;
const int width = 600;
double complex z = 0;

int main(void) {
    printf("Mandelbrot Set Vis");

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            double complex c = y + x * I;
            z = (z * z) + c;
            printf("z = %f + %fi\n", creal(z), cimag(z));
        }
    }
}
