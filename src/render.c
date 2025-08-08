#include "render.h"
#include "fractal.h"
#include "mandelbrot.h"

#include <raylib.h>
#include <stdint.h>
#include <stdlib.h>

void RenderMandelbrot(const RenderConfig* cfg, const Fractal* fractal) {
  if (!cfg || !fractal) {
    return;
  }

  InitWindow((int)cfg->width, (int)cfg->height, cfg->title);
  SetTargetFPS(cfg->maxFPS);

  uint16_t* iterBuffer = malloc(cfg->width * cfg->height * sizeof(int));
  if (!iterBuffer) {
    return;
  }

  if (fractal->type == FRACTAL_MANDELBROT) {
    mandelbrot(fractal, cfg->width, cfg->height, iterBuffer);
  }

  while (!WindowShouldClose()) {
    for (size_t y = 0; y < cfg->height; ++y) {
      for (size_t x = 0; x < cfg->width; ++x) {
        BeginDrawing();
        Color color;
        if (iterBuffer[y * cfg->width + x] == fractal->maxIter) {
          color = BLACK;
        } else {
          color = RED;
        }
        DrawPixel((int)y, (int)x, color);
      }
    }
    EndDrawing();
  }
  CloseWindow();
}
