# TBE (TaBouret Engine)

A 3D software renderer implemented in C++ without external graphics libraries (using only SDL2 for windowing and display).

## Features

- Support for basic shapes: Points, Lines, Rectangles, Squares, Triangles, Cuboids
- Real-time rendering with SDL2 display

## Dependencies

- C++17 compatible compiler
- CMake (for building)

## Build Instructions

2. Navigate to the project root directory.
3. Run the following command:

```bash
# To just build the project
make build

# To run the project
make run

# To remove the build directory and be able to make a clean build
make clean
```

## Project Structure

- `src/main.cpp`: Main entry point and rendering loop
- `src/Canvas/`: Canvas class for framebuffer management
- `src/Shapes/`: Shape classes (Point, Line, Rectangle, Square, Triangle, Cuboid)
- `src/constants.h`: Project constants (window size, FPS, etc.)

## Troubleshooting

- Ensure you have a C++17 compiler (GCC 7+, Clang 5+, or MSVC 2017+).
