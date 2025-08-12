#include "colour.h"
#include "status_codes.h"

#include <math.h>
#include <raylib.h>
#include <stdint.h>
#include <stdlib.h>

float* normaliseIterations(uint16_t* iterBuffer, size_t length,
                           float* normalisedValues) {
  if (length == 0 || !normalisedValues) {
    return NULL;
  }

  uint16_t min = iterBuffer[0];
  uint16_t max = iterBuffer[0];

  // find min & max
  for (size_t i = 1; i < length; ++i) {
    if (iterBuffer[i] < min) {
      min = iterBuffer[i];
    }
    if (iterBuffer[i] > max) {
      max = iterBuffer[i];
    }
  }

  // normalise as: norm = (original - min) / (max - min)
  for (size_t i = 0; i < length; ++i) {
    if (max == min) {
      normalisedValues[i] = 0.0f;
    } else {
      normalisedValues[i] = (iterBuffer[i] - min) / (float)(max - min);
    }
  }
  return normalisedValues;
}

int mapIterationToColor(float normalisedValue, Color* colour) {
  if (colour == NULL) {
    return COLOUR_ERR_NULL_POINTER;
  }

  if (normalisedValue < 0.0f || normalisedValue > 1.0f) {
    return COLOUR_ERR_NORMALISED_OUT_OF_RANGE;
  }

  // HSV: Hue, Sat, Val (Bright)
  float hue = normalisedValue * 360.0f;
  float sat = normalisedValue;
  float val = normalisedValue;

  hsv_to_rgba(hue, sat, val, &colour->r, &colour->g, &colour->b, &colour->a,
              UINT8_MAX);

  return FRACTAL_SUCCESS;
}

void hsv_to_rgba(float h, float s, float v, uint8_t* r, uint8_t* g, uint8_t* b,
                 uint8_t* a, uint8_t alpha) {
  float max = v;
  float c = s * v;
  float min = max - c;
  float R, G, B;
  h = h / 60;
  float x = c * (1.0f - fabsf(fmodf(h, 2.0f) - 1.0f));

  if (h >= 0 && h < 1)
    R = c, G = x, B = 0;
  else if (h >= 1 && h < 2)
    R = x, G = c, B = 0;
  else if (h >= 2 && h < 3)
    R = 0, G = c, B = x;
  else if (h >= 3 && h < 4)
    R = 0, G = x, B = c;
  else if (h >= 4 && h < 5)
    R = x, G = 0, B = c;
  else if (h >= 5 && h < 6)
    R = c, G = 0, B = x;
  else
    R = 0, G = 0, B = 0;

  R += min;
  B += min;
  G += min;

  *r = clamp8(R * 255.0f);
  *g = clamp8(G * 255.0f);
  *b = clamp8(B * 255.0f);

  *a = alpha;
}

uint8_t clamp8(float value) {
  if (value < 0.0f)
    return 0;
  if (value > 255.0f)
    return 255;
  return (uint8_t)value;
}
