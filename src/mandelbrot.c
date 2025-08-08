#include "mandelbrot.h"
#include <complex.h>
#include <stdlib.h>
#include "fractal.h"

// Mandelbrot set: z_{n+1} = z_n^2 + c
int mandelbrot(const Fractal* mandelbrot, const size_t width,
               const size_t height, uint16_t* iterBuffer) {
  if (!mandelbrot || !iterBuffer) {
    return MANDELBROT_FAILURE;
  }

  if (mandelbrot->type != FRACTAL_MANDELBROT) {
    return MANDELBROT_FAILURE;
  }

  for (size_t y = 0; y < height; ++y) {
    for (size_t x = 0; x < width; ++x) {
      // map pixel coordinate (x,y) to complex plane coordinate (cx, cy)
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
      iterBuffer[y * width + x] = (uint16_t)counter;
    }
  }
  return MANDELBROT_SUCCESS;
}
