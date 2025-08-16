# frctl

frctl is a fractal visualiser written in C using raylib, supporting Mandelbrot, Julia and Newton fractals.

---

# Demo

![Demo GIF](demo/demo3.gif)

---

# Keybinds

- `1`: mandelbrot
- `2`: julia
- `3`: newton
- `hold lmb`: drag in an area to zoom in
---

# Compilation & Running

> **Requirements:**
- raylib
- CMake >= 3.10
- C compiler (gcc, clang)
- UNIX System (Linux, MacOS, WSL)

```sh
mkdir build
cd build
cmake ..
make
cd ../bin
./frctl
```

---

# License

Licensed under the MIT License.
