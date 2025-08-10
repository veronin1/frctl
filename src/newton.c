#include "newton.h"
#include "fractal.h"
#include "status_codes.h"

#include <complex.h>
#include <stdint.h>

int newton(const Fractal* fractal, const size_t width, const size_t height,
           uint16_t* iterBuffer) {
  FractalStatus status =
      validate_fractal_inputs(fractal, width, height, iterBuffer);
  if (status != FRACTAL_SUCCESS) {
    return status;
  }

  for (size_t y = 0; y < height; ++y) {
    for (size_t x = 0; x < width; ++x) {
      iterBuffer[y * width + x] = newton_iter(fractal, x, y, width, height);
    }
  }
  return FRACTAL_SUCCESS;
}

uint16_t newton_iter(const Fractal* fractal, size_t x, size_t y,
                     const size_t width, const size_t height) {
  double zx =
      ((double)x / (double)width) * (fractal->maxReal - fractal->minReal) +
      fractal->minReal;
  double zy =
      ((double)y / (double)height) * (fractal->maxImag - fractal->minImag) +
      fractal->minImag;

  double complex z = CMPLX(zx, zy);

  size_t counter = 0;
  while (counter < fractal->maxIter) {
    z = (z * z) - ((z * z * z - 1) / 3 * z * z);
    counter++;

    if (cabs(z) < 1e-6) {
      break;
    }
  }
  return (uint16_t)counter;
}

complex double Function(complex double z) {
  return cpow(z, 3) - CMPLX(1.0, 0.0);
}

complex double Derivative(complex double z) {
  return 3.0 * (z * z);
}
