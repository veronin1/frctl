#ifndef COLOUR_H
#define COLOUR_H

#include <raylib.h>
#include <stdint.h>
#include <stdlib.h>

float* normaliseIterations(uint16_t* iterBuffer, size_t length);
int mapIterationToColor(float normalisedValue, Color* colour);

#endif
