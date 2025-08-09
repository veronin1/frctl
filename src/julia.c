// Julia set

#include "julia.h"
#include "fractal.h"

#include <stdint.h>

#define JULIA_SUCCESS 0;
#define JULIA_FAILURE -1;

// example coords:
// x,y
// 0.7111476192
// 0.2484631949

int julia(const Fractal* fractal, const size_t width, const size_t height) {
  if (!fractal || !height || !width) {
    return JULIA_FAILURE;
  }

  if (fractal->type != FRACTAL_JULIA) {
    return JULIA_FAILURE;
  }

  for (size_t y = 0; y < height; ++y) {
    for (size_t x = 0; x < width; ++x) {
      double zx =
          ((double)x / (double)width) * (fractal->maxReal - fractal->minReal) +
          fractal->minReal;
      double zy =
          ((double)y / (double)height) * (fractal->maxImag - fractal->minImag) +
          fractal->minImag;
      double complex c = 0;
    }
  }
  return JULIA_SUCCESS;
}

uint16_t julia_iterint(const Fractal* fractal, size_t x, size_t y, size_t width,
                       size_t height);
