#include "render.h"
#include "colour.h"
#include "fractal.h"
#include "julia.h"
#include "mandelbrot.h"
#include "newton.h"
#include "status_codes.h"

#include <math.h>
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
    goto cleanup;
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
      goto cleanup;
    default:
      goto cleanup;
  }

  normaliseIterations(iterBuffer, length, normalisedValues);
  Vector2 clickStart = {0};
  bool selecting = false;
  Vector2 currentPos = {0};

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(BLACK);

    if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
      clickStart = GetMousePosition();
      selecting = true;
    }

    if (selecting) {
      currentPos = GetMousePosition();
      DrawRectangleLines((int)clickStart.x, (int)clickStart.y,
                         (int)currentPos.x - (int)clickStart.x,
                         (int)currentPos.y - (int)clickStart.y, PINK);
    }

    if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT)) {
      selecting = false;

      double centerX = ((double)clickStart.x + (double)currentPos.x) / 2.0;
      double centerY = ((double)clickStart.y + (double)currentPos.y) / 2.0;
      double fractalCenterX = CartesianXToComplex(fractal, cfg, centerX);
      double fractalCenterY = CartesianYToComplex(fractal, cfg, centerY);

      double fractalX1 =
          CartesianXToComplex(fractal, cfg, (double)clickStart.x);
      double fractalX2 =
          CartesianXToComplex(fractal, cfg, (double)currentPos.x);
      double fractalWidth = fabs(fractalX2 - fractalX1);

      double fractalY1 =
          CartesianYToComplex(fractal, cfg, (double)clickStart.y);
      double fractalY2 =
          CartesianYToComplex(fractal, cfg, (double)currentPos.y);
      double fractalHeight = fabs(fractalY2 - fractalY1);

      fractal->minReal = fractalCenterX - fractalWidth / 2.0;
      fractal->maxReal = fractalCenterX + fractalWidth / 2.0;
      fractal->minImag = fractalCenterY - fractalHeight / 2.0;
      fractal->maxImag = fractalCenterY + fractalHeight / 2.0;

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
        default:
          goto cleanup;
      }

      normaliseIterations(iterBuffer, length, normalisedValues);
    }

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

double CartesianXToComplex(Fractal* fractal, const RenderConfig* cfg,
                           double pixelX) {
  return fractal->minReal + ((double)pixelX / (double)cfg->width) *
                                (fractal->maxReal - fractal->minReal);
}

double CartesianYToComplex(Fractal* fractal, const RenderConfig* cfg,
                           double pixelY) {
  return fractal->minImag + ((double)pixelY / (double)cfg->height) *
                                (fractal->maxImag - fractal->minImag);
}
