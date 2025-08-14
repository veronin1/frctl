#ifndef RENDER_H
#define RENDER_H

#include "fractal.h"

#include <bits/pthreadtypes.h>
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

typedef struct TileQueue {
  Tile* Tiles;
  int count;
  int next;
  pthread_mutex_t lock;
} TileQueue;

void RenderFractal(const RenderConfig *cfg, Fractal *fractal);
double CartesianXToComplex(Fractal* fractal,  const RenderConfig *cfg, double pixelX);
double CartesianYToComplex(Fractal* fractal,  const RenderConfig *cfg, double pixelY);

#endif // RENDER_H
