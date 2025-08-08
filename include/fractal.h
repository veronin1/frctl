#ifndef FRACTAL_H
#define FRACTAL_H

#include <stdlib.h>

typedef struct {
    double minReal, maxReal;
    double minImag, maxImag;
    size_t maxIter;
} Fractal;

#endif // FRACTAL.H
