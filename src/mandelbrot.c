#include "mandelbrot.h"
#include <complex.h>
#include <stdlib.h>

int mandelbrot(Fractal* mandelbrot, size_t width, size_t height) {
  for (size_t y = 0; y < height; ++y) {
    for (size_t x = 0; x < width; ++x) {
      // z_new = z_old * z_old + c
      double cx = ((double)x / (double)width) *
                      (mandelbrot->maxReal - mandelbrot->minReal) +
                  mandelbrot->minReal;
      double cy = ((double)y / (double)height) *
                      (mandelbrot->maxImag - mandelbrot->minImag) +
                  mandelbrot->minImag;

      double complex c = CMPLX(cx, cy);
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
