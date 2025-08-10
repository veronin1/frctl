#include "colour.h"

#include <raylib.h>
#include <stdlib.h>

float normaliseIterations(uint16_t* iterBuffer, size_t length) {
  float min = 0, max = 0;

  for (size_t i = 1; i < length; ++i) {
    if (iterBuffer[i] < min)
      min = iterBuffer[i];
    if (iterBuffer[i] > max)
      max = iterBuffer[i];
  }
}

Color mapIterationToColor(uint16_t iteration, Color* colour) {
  float normalisedIteration = (iteration - 0) / (1 - 0) * 1;
}
