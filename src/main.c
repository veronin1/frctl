#include <complex.h>
#include <raylib.h>
#include "fractal.h"
#include "render.h"

/* MANDELBROT
  fractal->minReal = -2.0;
  fractal->maxReal = 1.0;
  fractal->minImag = -1.5;
  fractal->maxImag = 1.5;
  fractal->maxIter = 1000;

  JULIA
  fractal->minReal = -1.5;
  fractal->maxReal = 1.5;
  fractal->minImag = -1.5;
  fractal->maxImag = 1.5;
  fractal->maxIter = 100;

  NEWTON
  fractal->minReal = -2.0;
  fractal->maxReal = 2.0;
  fractal->minImag = -2.0;
  fractal->maxImag = 2.0;
  fractal->maxIter = 1000;
 */

int main(void) {
  Fractal* fractal = malloc(sizeof(Fractal));
  if (!fractal) {
    return 1;
  }

  fractal->type = FRACTAL_JULIA;
  fractal->minReal = -1.5;
  fractal->maxReal = 1.5;
  fractal->minImag = -1.5;
  fractal->maxImag = 1.5;
  fractal->maxIter = 10000;

  RenderConfig* cfg = malloc(sizeof(RenderConfig));
  if (!cfg) {
    free(fractal);
    return 1;
  }
  cfg->height = 1440;
  cfg->width = 2560;
  cfg->title = "frctl";
  cfg->maxFPS = 60;

  RenderFractal(cfg, fractal);

  free(fractal);
  free(cfg);
  return 0;
}
