#ifndef NEWTON_H
#define NEWTON_H

#include "fractal.h"
#include <stdint.h>
#include <complex.h>

int newton(const Fractal *fractal, const size_t width, const size_t height,
           uint16_t *iterBuffer);

uint16_t newton_iter(const Fractal *fractal, size_t x, size_t y,
                     const size_t width, const size_t height);
complex double Function(complex double z);
complex double Derivative(complex double z);

#endif // NEWTON.H
