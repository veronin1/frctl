#ifndef MANDELBROT_H
#define MANDELBROT_H

#include "fractal.h"

#include <stdint.h>

int mandelbrot_tile(const Fractal* fractal, size_t startX, size_t startY, size_t tileWidth, size_t tileHeight, uint16_t* iterBuffer, size_t imageWidth, size_t imageHeight);
int mandelbrot(const Fractal* mandelbrot,const size_t width, const size_t height, uint16_t* iterBuffer);
uint16_t mandelbrot_iter(const Fractal* fractal, size_t x, size_t y,
                         size_t width, size_t height);

#endif // MANDELBROT_H
