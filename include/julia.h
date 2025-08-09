#ifndef JULIA_H
#define JULIA_H

#include "fractal.h"
#include <stdint.h>

int julia(const Fractal *fractal, const size_t width,
          const size_t height, uint16_t* iterBuffer);
uint16_t julia_iter(const Fractal* fractal, size_t x, size_t y, size_t width,
                       size_t height);

#endif // JULIA_H

