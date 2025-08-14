#ifndef JULIA_H
#define JULIA_H

#include "fractal.h"
#include "render.h"
#include <stdint.h>

int julia_tile(const Fractal* fractal, const Tile* tile, uint16_t* iterBuffer, size_t imageWidth, size_t imageHeight);
int julia(const Fractal *fractal, const size_t width,
          const size_t height, uint16_t* iterBuffer);
uint16_t julia_iter(const Fractal* fractal, size_t x, size_t y, size_t width,
                       size_t height);

#endif // JULIA_H

