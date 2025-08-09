// Julia set

#include "julia.h"
#include "fractal.h"

#include <complex.h>
#include <stdint.h>

int julia(const Fractal* fractal, const size_t width, const size_t height,
          uint16_t* iterBuffer) {
  if (!fractal || !height || !width) {
    return JULIA_FAILURE;
  }

  if (fractal->type != FRACTAL_JULIA) {
    return JULIA_FAILURE;
  }

  for (size_t y = 0; y < height; ++y) {
    for (size_t x = 0; x < width; ++x) {
      iterBuffer[y * width + x] = julia_iter(fractal, x, y, width, height);
    }
  }
  return JULIA_SUCCESS;
}

uint16_t julia_iter(const Fractal* fractal, size_t x, size_t y, size_t width,
                    size_t height) {
  double zx =
      ((double)x / (double)width) * (fractal->maxReal - fractal->minReal) +
      fractal->minReal;
  double zy =
      ((double)y / (double)height) * (fractal->maxImag - fractal->minImag) +
      fractal->minImag;
  double complex c = CMPLX(-0.7, 0.27015);
  double complex z = CMPLX(zx, zy);

  size_t counter = 0;

  while (cabs(z) < 2 && counter < fractal->maxIter) {
    z = z * z + c;
    ++counter;
  }
  return (uint16_t)counter;
}
