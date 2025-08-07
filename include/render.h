typedef struct {
    int width, height;
    char* title;
    int maxFPS;
    double minReal, maxReal;
    double minImag, maxImag;
} RenderConfig;

void RenderMandelbrot(const RenderConfig* cfg);
