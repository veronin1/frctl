#ifndef MANDELBROT_H
#define MANDELBROT_H

#include "fractal.h"

#define MANDELBROT_SUCCESS 0
#define MANDELBROT_FAILURE -1

int mandelbrot(Fractal* mandelbrot, size_t width, size_t height);

#endif // MANDELBROT_H
