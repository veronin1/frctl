#ifndef FRACTAL_H
#define FRACTAL_H

#include "status_codes.h"
#include <stdlib.h>
#include <stdint.h>

typedef enum {
  FRACTAL_MANDELBROT,
  FRACTAL_JULIA,
  FRACTAL_BURNINGSHIP
} FractalType;

typedef struct {
  FractalType type;
  double minReal, maxReal;
    double minImag, maxImag;
    size_t maxIter;
} Fractal;


// Validate inputs relevant to fractal
FractalStatus validate_fractal_inputs(const Fractal* fractal, size_t width, size_t height, const uint16_t* iterBuffer);

#endif // FRACTAL.H
