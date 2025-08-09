#ifndef RENDER_H
#define RENDER_H

#include "fractal.h"

#include <stdlib.h>


typedef struct {
    size_t width, height;
    char* title;
    int maxFPS;
} RenderConfig;

void RenderFractal(const RenderConfig* cfg, const Fractal* fractal);

#endif // RENDER_H
