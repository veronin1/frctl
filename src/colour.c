#include "colour.h"

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
      normalisedValues[i] = (float)(iterBuffer[i] - min) / (max - min);
    }
  }
  return normalisedValues;
}

Color* mapIterationToColor(uint16_t iteration, Color* colour) {
  // to codes
  return colour;
}
