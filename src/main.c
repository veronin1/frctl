#include <complex.h>
#include <raylib.h>
#include <stdlib.h>

// raylib window related consts
const int height = 800;
const int width = 800;
const char* title = "mandel";
const int maxFPS = 60;

// mandelbrot related consts
const double max_real = 1.0;
const double min_real = -2.0;
const double max_imag = 1.5;
const double min_imag = -1.5;
const size_t maxIter = 1000;

void RenderMandelbrot(const int height, const int width, const char* title,
                      const int maxFPS, const double max_real,
                      const double min_real, const double max_imag,
                      const double min_imag) {
    InitWindow(width, height, title);
    SetTargetFPS(maxFPS);
}

int main(void) {
    RenderMandelbrot(width, width, title, maxFPS, max_real, min_real, max_imag,
                     min_imag);

    InitWindow(width, height, title);
    SetTargetFPS(maxFPS);
    int currentMonitor = GetCurrentMonitor();

    while (!WindowShouldClose()) {
        int newMonitor = GetCurrentMonitor();

        if (currentMonitor != newMonitor) {
            currentMonitor = newMonitor;

            SetWindowSize(GetMonitorWidth(currentMonitor),
                          GetMonitorHeight(currentMonitor));

            SetTargetFPS(GetMonitorRefreshRate(currentMonitor));
        }

        BeginDrawing();

        for (int y = 0; y < height; ++y) {
            for (int x = 0; x < width; ++x) {

                double cx =
                    ((double)x / width) * (max_real - min_real) + min_real;
                double cy =
                    ((double)y / height) * (max_imag - min_imag) + min_imag;
                double complex c = cx + cy * I;
                double complex z = 0;

                size_t counter = 0;
                while (cabs(z) <= 2 && counter < maxIter) {
                    z = z * z + c;
                    counter++;
                }

                Color color;
                if (counter == maxIter) {
                    // BLACK
                    color = (Color){0, 0, 0, 255};
                } else {
                    if (counter < 250)
                        color = RED;
                    if (counter > 250 && counter < 500)
                        color = BLUE;
                    if (counter > 500 && counter < 750)
                        color = YELLOW;
                    if (counter > 750 && counter < 1000)
                        color = GREEN;
                }

                DrawPixel(x, y, color);
            }
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
