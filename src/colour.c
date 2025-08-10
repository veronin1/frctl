#include "colour.h"
#include "status_codes.h"

#include <raylib.h>
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

  normalisedValue *= 255;
  colour->r = (uint8_t)normalisedValue;
  colour->b = (uint8_t)normalisedValue;
  colour->g = (uint8_t)normalisedValue;
  colour->a = 255;

  return FRACTAL_SUCCESS;
}
