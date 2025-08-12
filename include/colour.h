#ifndef COLOUR_H
#define COLOUR_H

#include <raylib.h>
#include <stdint.h>
#include <stdlib.h>

float* normaliseIterations(uint16_t* iterBuffer, size_t length, float* normalisedValues);
int mapIterationToColor(float normalisedValue, Color* colour);
void hsv_to_rgba(float h, float s, float v, uint8_t *r, uint8_t *g, uint8_t *b,
                 uint8_t *a, uint8_t alpha);
uint8_t clamp8(float value);


#endif
