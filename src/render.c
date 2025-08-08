#include "render.h"
#include <raylib.h>

#include "mandelbrot.h"

void RenderMandelbrot(const RenderConfig* cfg, const Fractal* fractal) {
  InitWindow((int)cfg->width, (int)cfg->height, cfg->title);
  SetTargetFPS(cfg->maxFPS);

  while (!WindowShouldClose()) {
    //
  }
  CloseWindow();
}
