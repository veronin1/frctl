#include "mandelbrot.h"
#include <complex.h>
#include <stdlib.h>

const int height = 800;
const int width = 800;

int mandelbrot(Fractal* mandelbrot) {
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
    return MANDELBROT_SUCCESS;
}
