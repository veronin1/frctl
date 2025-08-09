#ifndef FRACTAL_H
#define FRACTAL_H

#include <stdlib.h>

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

#endif // FRACTAL.H
