#include <complex.h>
#include <stdlib.h>

#define MANDELBROT_SUCCESS 0
#define MANDELBROT_FAILURE -1

typedef struct {
    double minReal, maxReal;
    double minImag, maxImag;
    size_t maxIter;
} Fractal;

const int height, width = 800;

void mandelbrot(Fractal* mandelbrot) {
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            // z_new = z_old * z_old + c
            double cx = ((double)x / width) *
                            (mandelbrot->maxReal - mandelbrot->minReal) +
                        mandelbrot->minReal;
            double cy = ((double)y / height) *
                            (mandelbrot->maxImag - mandelbrot->minImag) +
                        mandelbrot->minImag;

            double complex c = cx + cy * I;
            double complex z = 0;

            size_t counter = 0;
            while (cabs(z) <= 2 && counter < mandelbrot->maxIter) {
                z = z * z + c;
                ++counter;
            }
        }
    }
}
