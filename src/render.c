#include "render.h"
#include "colour.h"
#include "fractal.h"
#include "julia.h"
#include "mandelbrot.h"
#include "newton.h"
#include "status_codes.h"

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

  size_t length = cfg->width * cfg->height;

  float* normalisedValues = normaliseIterations(iterBuffer, length);

  while (!WindowShouldClose()) {
    BeginDrawing();
    for (size_t y = 0; y < cfg->height; ++y) {
      for (size_t x = 0; x < cfg->width; ++x) {
        float normalisedValue = normalisedValues[y * cfg->width + x];
        Color colour;

        int status = mapIterationToColor(normalisedValue, &colour);
        if (status != FRACTAL_SUCCESS) {
          break;
        }

        DrawPixel((int)x, (int)y, colour);
      }
    }
    EndDrawing();
  }
  free(normalisedValues);
  free(iterBuffer);
  CloseWindow();
}
