#ifndef RENDER_H
#define RENDER_H

#include "fractal.h"

#include <stdlib.h>

typedef struct {
    size_t width, height;
    char* title;
    int maxFPS;
} RenderConfig;

typedef struct {
  int startX, startY;
  int width, height;
} Tile;

void RenderFractal(const RenderConfig *cfg, Fractal *fractal);
double CartesianXToComplex(Fractal* fractal,  const RenderConfig *cfg, double pixelX);
double CartesianYToComplex(Fractal* fractal,  const RenderConfig *cfg, double pixelY);

#endif // RENDER_H
