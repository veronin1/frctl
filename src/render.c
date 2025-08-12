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

void RenderFractal(const RenderConfig* cfg, Fractal* fractal) {
  if (!cfg || !fractal) {
    return;
  }

  InitWindow((int)cfg->width, (int)cfg->height, cfg->title);
  SetTargetFPS(cfg->maxFPS);

  size_t length = cfg->width * cfg->height;

  float* normalisedValues = malloc(length * sizeof(float));
  uint16_t* iterBuffer = calloc(cfg->width * cfg->height, sizeof(uint16_t));
  if (!normalisedValues || !iterBuffer) {
    free(iterBuffer);
    free(normalisedValues);
    CloseWindow();
    return;
  }

  switch (fractal->type) {
    case FRACTAL_MANDELBROT:
      mandelbrot(fractal, cfg->width, cfg->height, iterBuffer);
      break;
    case FRACTAL_JULIA:
      julia(fractal, cfg->width, cfg->height, iterBuffer);
      break;
    case FRACTAL_NEWTON:
      newton(fractal, cfg->width, cfg->height, iterBuffer);
      break;
    case FRACTAL_BURNINGSHIP:
      // do nothing
    default:
      goto cleanup;
  }

  normaliseIterations(iterBuffer, length, normalisedValues);

  while (!WindowShouldClose()) {
    BeginDrawing();
    for (size_t y = 0; y < cfg->height; ++y) {
      for (size_t x = 0; x < cfg->width; ++x) {
        float normalisedValue = normalisedValues[y * cfg->width + x];
        Color colour;

        if (mapIterationToColor(normalisedValue, &colour) != FRACTAL_SUCCESS) {
          goto cleanup;
        }
        DrawPixel((int)x, (int)y, colour);
      }
    }
    EndDrawing();
  }

cleanup:
  free(normalisedValues);
  free(iterBuffer);
  CloseWindow();
}
