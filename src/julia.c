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
}

uint16_t julia_iterint(const Fractal* fractal, size_t x, size_t y, size_t width,
                       size_t height);
