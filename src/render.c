#include "mandelbrot.h"
#include <raylib.h>
typedef struct {
    int width, height;
    char* title;
    int maxFPS;
    double minReal, maxReal;
    double minImag, maxImag;
} RenderConfig;

void RenderMandelbrot(const RenderConfig* cfg) {
    InitWindow(cfg->width, cfg->height, cfg->title);
    SetTargetFPS(cfg->maxFPS);

    while (!WindowShouldClose()) {
        //
    }
    CloseWindow();
}
