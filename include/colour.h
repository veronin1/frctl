#ifndef COLOUR_H
#define COLOUR_H

#include <raylib.h>
#include <stdint.h>
#include <stdlib.h>

float* normaliseIterations(uint16_t* iterBuffer, size_t length);
int mapIterationToColor(float normalisedValue, Color* colour);
void hsv_to_rgb(float h, float s, float v, uint8_t* r, uint8_t* g, uint8_t* b);


#endif
