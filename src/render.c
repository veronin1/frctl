#include "render.h"
#include "fractal.h"
#include "julia.h"
#include "mandelbrot.h"
#include "newton.h"

#include <raylib.h>
#include <stdint.h>
#include <stdlib.h>

void RenderFractal(const RenderConfig* cfg, const Fractal* fractal) {
  if (!cfg || !fractal) {
    return;
  }

  InitWindow((int)cfg->width, (int)cfg->height, cfg->title);
  SetTargetFPS(cfg->maxFPS);

  uint16_t* iterBuffer = calloc(cfg->width * cfg->height, sizeof(uint16_t));
  if (!iterBuffer) {
    CloseWindow();
    return;
  }

  if (fractal->type == FRACTAL_MANDELBROT) {
    mandelbrot(fractal, cfg->width, cfg->height, iterBuffer);
  } else if (fractal->type == FRACTAL_JULIA) {
    julia(fractal, cfg->width, cfg->height, iterBuffer);
  } else if (fractal->type == FRACTAL_NEWTON) {
    newton(fractal, cfg->width, cfg->height, iterBuffer);
  } else {
    free(iterBuffer);
    CloseWindow();
    return;
  }

  while (!WindowShouldClose()) {
    BeginDrawing();
    for (size_t y = 0; y < cfg->height; ++y) {
      for (size_t x = 0; x < cfg->width; ++x) {
        uint16_t iter = iterBuffer[y * cfg->width + x];
        Color color;
        if (iter == fractal->maxIter) {
          color = BLACK;
        } else {
          color = RED;
        }
        DrawPixel((int)x, (int)y, color);
      }
    }
    EndDrawing();
  }
  CloseWindow();
  free(iterBuffer);
}
