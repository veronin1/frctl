#ifndef STATUS_CODES_H
#define STATUS_CODES_H

typedef enum {
  FRACTAL_SUCCESS = 0,
  FRACTAL_FAILURE = -1,
  FRACTAL_ERR_NULL_POINTER = -2,
  FRACTAL_ERR_INVALID_DIMENSIONS = -3,
  FRACTAL_ERR_WRONG_TYPE = -4,
  FRACTAL_ERR_NULL_ITERBUFFER = -5,

  // fractacsl specfiic error codes start at 100
  FRACTAL_ERR_BASE = -100,

  // fractal (error = FRACTAL_ERR_BASE - 1...
} FractalStatus;

#endif // STATUS_CODES_H
