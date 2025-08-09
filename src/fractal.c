#include "fractal.h"
#include "status_codes.h"

FractalStatus validate_fractal_inputs(const Fractal* fractal, size_t width,
                                      size_t height,
                                      const uint16_t* iterBuffer) {
  if (!fractal) {
    return FRACTAL_ERR_NULL_POINTER;
  }

  if (height == 0 || width == 0) {
    return FRACTAL_ERR_INVALID_DIMENSIONS;
  }

  if (!iterBuffer) {
    return FRACTAL_ERR_NULL_ITERBUFFER;
  }
  return FRACTAL_SUCCESS;
}
