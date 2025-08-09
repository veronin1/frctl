cmake_minimum_required(VERSION 3.10)
project(frctl C)

# Compiler setup
set(CMAKE_C_COMPILER clang)

# Enable clang-tidy if available
option(USE_CLANG_TIDY "Enable clang-tidy" ON)
if(USE_CLANG_TIDY)
    find_program(CLANG_TIDY_EXE NAMES "clang-tidy")
    if(CLANG_TIDY_EXE)
        set(CMAKE_C_CLANG_TIDY "${CLANG_TIDY_EXE}")
    endif()
endif()

# Export compile_commands.json for LSP/clang-tidy
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Output directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

# Source files
add_executable(frctl
    src/main.c
    src/mandelbrot.c
    src/render.c
    src/julia.c
    src/fractal.c
)

# Include directories
target_include_directories(frctl PRIVATE ${CMAKE_SOURCE_DIR}/include)

# raylib
find_package(raylib REQUIRED)
target_link_libraries(frctl PRIVATE raylib)

# Compiler warnings and hardening
target_compile_options(frctl PRIVATE
    -Wall
    -Wextra
    -Wpedantic
    -Wshadow
    -Wformat=2
    -Wcast-align
    -Wconversion
    -Wnull-dereference
    -Wdouble-promotion
    -Wpointer-arith
    -Werror
    -Wunreachable-code
    -Wmissing-prototypes
    -Wstrict-prototypes
    -Wimplicit-fallthrough
    -Wold-style-definition
    -fstack-protector-strong
    -fsanitize=address
    -O3
    -g
)

# Definitions
target_compile_definitions(frctl PRIVATE _FORTIFY_SOURCE=2)

# Linker options
target_link_options(frctl PRIVATE -fsanitize=address)

