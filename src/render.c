#include "render.h"
#include "colour.h"
#include "fractal.h"
#include "julia.h"
#include "mandelbrot.h"
#include "newton.h"
#include "status_codes.h"

#include <math.h>
#include <pthread.h>
#include <raylib.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

void RenderFractal(const RenderConfig* cfg, Fractal* fractal) {
  if (!cfg || !fractal) {
    return;
  }

  InitWindow((int)cfg->width, (int)cfg->height, cfg->title);
  SetTargetFPS(cfg->maxFPS);

  size_t length = cfg->width * cfg->height;

  float* normalisedValues = NULL;
  uint16_t* iterBuffer = NULL;
  Tile* tiles = NULL;
  TileQueue* tQueue = NULL;
  pthread_t* threads = NULL;

  normalisedValues = malloc(length * sizeof(float));
  iterBuffer = calloc(cfg->width * cfg->height, sizeof(uint16_t));
  if (!normalisedValues || !iterBuffer) {
    goto cleanup;
  }

  /*
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

  */

  bool fractalTypeChanged = false;
  
  
  normaliseIterations(iterBuffer, length, normalisedValues);
  Vector2 clickStart = {0};
  bool selecting = false;
  Vector2 currentPos = {0};

  Image img = GenImageColor((int)cfg->width, (int)cfg->height, BLACK);
  Texture2D tex = LoadTextureFromImage(img);

  size_t tilesX = (cfg->width + 31) / 32;
  size_t tilesY = (cfg->height + 31) / 32;
  size_t totalTiles = tilesX * tilesY;

  tiles = malloc((unsigned long)totalTiles * sizeof(Tile));
  tQueue = malloc(sizeof(TileQueue));
  if (!tiles || !tQueue) {
    goto cleanup;
  }

  for (size_t y = 0; y < tilesY; ++y) {
    for (size_t x = 0; x < tilesX; ++x) {
      size_t index = y * tilesX + x;
      tiles[index].height = 32;
      tiles[index].width = 32;
      tiles[index].startX = x * 32;
      tiles[index].startY = y * 32;
    }
  }

  tQueue->Tiles = tiles;
  tQueue->next = 0;
  tQueue->count = totalTiles;
  pthread_mutex_init(&tQueue->lock, NULL);

  long cores = sysconf(_SC_NPROCESSORS_ONLN);
  if (cores <= 0) {
    cores = 1;
  }

  threads = malloc(sizeof(pthread_t) * (unsigned long)cores);

  while (!WindowShouldClose()) {

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
    
      WorkerArgs* args = malloc(sizeof(WorkerArgs));
      args->queue = tQueue;
      args->fractal = fractal;
      args->iterBuffer = iterBuffer;
      tQueue->next = 0;
      args->imageHeight = (size_t)img.height;
      args->imageWidth = (size_t)img.width;

      for (size_t i = 0; i < (size_t)cores; ++i) {
        int rc =
            pthread_create(&threads[i], NULL, (void* (*)(void*))worker, args);
        if (rc != 0) {
          goto cleanup;
        }
      }

      for (size_t i = 0; i < (size_t)cores; ++i) {
        pthread_join(threads[i], NULL);
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
        ((Color*)img.data)[y * cfg->width + x] = colour;
      }
    }
    UpdateTexture(tex, img.data);

    BeginDrawing();
    ClearBackground(BLACK);
    DrawTexture(tex, 0, 0, WHITE);
    EndDrawing();

    if (IsKeyPressed(KEY_ONE)) {
      fractal->type = FRACTAL_MANDELBROT;
      fractalTypeChanged = true;
    }
    if (IsKeyPressed(KEY_TWO)) {
      fractal->type = FRACTAL_JULIA;
      fractalTypeChanged = true;
    }
    if (IsKeyPressed(KEY_THREE)) {
      fractal->type = FRACTAL_NEWTON;
      fractalTypeChanged = true;
    }
  }

  UnloadTexture(tex);
  UnloadImage(img);

cleanup:
  free(normalisedValues);
  free(iterBuffer);
  free(tQueue);
  free(tiles);
  free(threads);
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

void* worker(WorkerArgs* args) {
  while (true) {
    pthread_mutex_lock(&args->queue->lock);
    if (args->queue->next >= args->queue->count) {
      pthread_mutex_unlock(&args->queue->lock);
      break;
    }

    const Tile tile = args->queue->Tiles[args->queue->next];
    args->queue->next++;
    pthread_mutex_unlock(&args->queue->lock);

    switch (args->fractal->type) {
      case FRACTAL_MANDELBROT:
        mandelbrot_tile(args->fractal, &tile, args->iterBuffer,
                        args->imageWidth, args->imageHeight);
        break;
      case FRACTAL_JULIA:
        julia_tile(args->fractal, &tile, args->iterBuffer, args->imageWidth,
                   args->imageHeight);
        break;
      case FRACTAL_NEWTON:
        newton_tile(args->fractal, &tile, args->iterBuffer, args->imageWidth,
                    args->imageHeight);
        break;
      default:
        break;
    }
  }
  return NULL;
}

void renderFractal(Fractal* fractal, const RenderConfig* cfg, uint16_t* iterBuffer, float* normalisedValues) {
 
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
      break;
  }

  normaliseIterations(iterBuffer, cfg->width * cfg->height, normalisedValues);
}
