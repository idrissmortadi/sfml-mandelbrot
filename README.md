# Mandelbrot Fractal Visualizer

This project is a Mandelbrot fractal visualizer created using C++ and the SFML (Simple and Fast Multimedia Library) framework. The application renders the Mandelbrot set in real-time, allowing users to explore the fractal's intricate patterns through panning and zooming.

[Demo video](demo.mp4)

## Features

- **Real-Time Rendering**: View the Mandelbrot set with real-time updates.
- **Interactive Controls**: Use keyboard inputs to pan and zoom through the fractal.
- **Dynamic Fractal Calculation**: Recalculate the fractal when zooming or panning to reflect changes.

## Getting Started

To build and run the visualizer, ensure you have SFML and CMake are installed. Compile the project and execute the resulting binary to start exploring the Mandelbrot set.
```bash
cmake --build build --config Release && ./build/bin/main
```

## Usage

- **Arrow Keys / WASD**: Pan the view.
- **A / E**: Zoom in / out.
- **Space Bar**: Recalculate the fractal image.

Enjoy exploring the endless complexities of the Mandelbrot fractal!

