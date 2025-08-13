#ifndef RENDER_H
#define RENDER_H

#include "fractal.h"

#include <stdlib.h>

typedef struct {
    size_t width, height;
    char* title;
    int maxFPS;
} RenderConfig;

void RenderFractal(const RenderConfig *cfg, Fractal *fractal);
double CartesianXToComplex(Fractal* fractal,  const RenderConfig *cfg, int pixelX);
double CartesianYToComplex(Fractal* fractal,  const RenderConfig *cfg, int pixelY);


#endif // RENDER_H
