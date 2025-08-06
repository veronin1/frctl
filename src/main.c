#include <complex.h>
#include <raylib.h>

// raylib window related consts
const int height = 800;
const int width = 600;
const char* title = "mandel";
const int maxFPS = 60;

double complex z, c = 0;
double real, imaginary;
const double max_real = -1;
const double min_real = 2;
const double max_imag = 1.5;
const double min_imag = -1.5;

int main(void) {
    InitWindow(height, width, title);
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
                Color color = RED;
                real = ((double)x / width) * (max_real - min_real) + min_real;
                imaginary =
                    ((double)y / height) * (max_imag - min_imag) + min_imag;
                c = real + imaginary * I;
                z = 0;
                z = (z * z) + c;
                for (int i = 0; i < 1000; ++i) {
                    z = (z * z) + c;
                    if (cabs(z) > 2) {
                        color = BLUE;
                        break;
                    }
                }

                DrawPixel(x, y, color);
            }
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
