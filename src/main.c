#include <complex.h>
#include <raylib.h>
#include <stdlib.h>

// raylib window related consts
const int height = 800;
const int width = 800;
const char* title = "mandel";
const int maxFPS = 60;

// mandelbrot related consts
double real, imaginary;
const double max_real = 1.0;
const double min_real = -2.0;
const double max_imag = 1.5;
const double min_imag = -1.5;

int main(void) {
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
                size_t maxIter = 1000;
                while (cabs(z) >= 2 && counter < maxIter) {
                    z = z * z + c;
                    counter++;
                }

                Color color;
                if (counter == maxIter) {
                    color = BLACK;
                } else {
                    color = RED;
                }

                DrawPixel(x, y, color);
            }
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
