#include "mandelbrot.h"
#include "fractal.h"
#include "status_codes.h"

#include <complex.h>
#include <stdlib.h>

int mandelbrot_tile(const Fractal* fractal, size_t startX, size_t startY,
                    size_t tileWidth, size_t tileHeight, uint16_t* iterBuffer,
                    size_t imageWidth, size_t imageHeight) {
  if (!fractal || !iterBuffer) {
    return FRACTAL_ERR_NULL_POINTER;
  }

  for (size_t y = 0; y < tileHeight; ++y) {
    for (size_t x = 0; x < tileWidth; ++x) {
      size_t px = startX + x;
      size_t py = startY + y;
      if (px >= imageWidth || py >= imageHeight) {
        continue;
      }
      iterBuffer[py * imageWidth + px] =
          mandelbrot_iter(fractal, x, y, imageWidth, imageHeight);
    }
  }
  return FRACTAL_SUCCESS;
}

// Mandelbrot set: z_{n+1} = z_n^2 + c
int mandelbrot(const Fractal* fractal, const size_t width, const size_t height,
               uint16_t* iterBuffer) {
  FractalStatus status =
      validate_fractal_inputs(fractal, width, height, iterBuffer);
  if (status != FRACTAL_SUCCESS) {
    return status;
  }

  if (fractal->type != FRACTAL_MANDELBROT) {
    return FRACTAL_ERR_WRONG_TYPE;
  }

  for (size_t y = 0; y < height; ++y) {
    for (size_t x = 0; x < width; ++x) {
      iterBuffer[y * width + x] = mandelbrot_iter(fractal, x, y, width, height);
      ;
    }
  }
  return FRACTAL_SUCCESS;
}

uint16_t mandelbrot_iter(const Fractal* fractal, size_t x, size_t y,
                         size_t width, size_t height) {
  double cx =
      ((double)x / (double)width) * (fractal->maxReal - fractal->minReal) +
      fractal->minReal;
  double cy =
      ((double)y / (double)height) * (fractal->maxImag - fractal->minImag) +
      fractal->minImag;

  double complex c = CMPLX(cx, cy);
  double complex z = 0;

  size_t counter = 0;
  while (cabs(z) <= 2 && counter < fractal->maxIter) {
    z = z * z + c;
    ++counter;
  }
  return (uint16_t)counter;
}
