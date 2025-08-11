#include "colour.h"
#include "status_codes.h"

#include <math.h>
#include <raylib.h>
#include <stdint.h>
#include <stdlib.h>

float* normaliseIterations(uint16_t* iterBuffer, size_t length) {
  if (length == 0) {
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

  // array of normalised floats
  float* normalisedValues = malloc(length * sizeof(float));
  if (!normalisedValues) {
    return NULL;
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
  // uint8_t sat = (uint8_t)normalisedValue * (uint8_t)100;
  // uint8_t val = (uint8_t)normalisedValue * (uint8_t)100;

  colour->a = 255;

  if (hue >= 0 && hue <= 60) {
    colour->r = 255;
    colour->g = (uint8_t)((hue / 60.0f) * 255.0f);
    colour->b = 0;
  } else if (hue >= 60 && hue <= 120) {
    colour->r = (uint8_t)(((120.0f - hue) / 60.0f) * 255.0f);
    colour->g = 0;
    colour->b = 255;
  } else if (hue >= 120 && hue <= 180) {
    colour->r = 0;
    colour->b = 255;
    colour->g = (uint8_t)(((hue - 120.0f) / 60.0f) * 255.0f);
  } else if (hue >= 180 && hue <= 240) {
    colour->r = 0;
    colour->b = (uint8_t)(((240.0f - hue) / 60.0f) * 255.0f);
    colour->g = 255;
  } else if (hue >= 240 && hue <= 300) {
    colour->r = (uint8_t)(((hue - 240.0f) / 60.0f) * 255.0f);
    colour->g = 0;
    colour->b = 255;
  } else if (hue >= 300 && hue <= 360) {
    colour->r = 255;
    colour->g = 0;
    colour->b = (uint8_t)(((360.0f - hue) / 60.0f) * 255.0f);
  }

  return FRACTAL_SUCCESS;
}

void hsv_to_rgb(float h, float s, float v, uint8_t* r, uint8_t* g, uint8_t* b) {
  float max = v;
  float c = s * v;
  float min = max - c;
  float R, G, B;
  h = h / 60; // h /= 60
  float x = c * (1.0f - fabsf(fmodf(h, 2.0f) - 1.0f));

  if (h <= 0 && h < 1) {
    R = c;
    G = x;
    B = 0;
  } else if (h <= 1 && h < 2) {
    R = x;
    G = c;
    B = 0;
  } else if (h <= 2 && h < 3) {
    R = 0;
    G = c;
    B = x;
  } else if (h <= 3 && h < 4) {
    R = 0;
    G = x;
    B = c;
  } else if (h <= 4 && h <= 5) {
    R = x;
    G = 0;
    B = c;
  } else if (h <= 5 && h < 6) {
    R = c;
    G = 0;
    B = x;
  } else {
    R = 0;
    G = 0;
    B = 0;
  }

  R += min;
  B += min;
  G += min;

  *r = (uint8_t)(R * 255.0f);
  *g = (uint8_t)(G * 255.0f);
  *b = (uint8_t)(B * 255.0f);
}
