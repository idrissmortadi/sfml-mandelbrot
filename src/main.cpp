#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <complex>

// Constants
#define WIDTH 800
#define HEIGHT 600
#define COLOR_CHANNELS 4 // RGBA
#define MAX_ITER 500

#define MOVE_SPEED 10
#define ZOOM_LEVEL 0.05

// Function to calculate Mandelbrot and fill the pixel array
void calculateMandelbrot(sf::Uint8 *pixels, double centerX, double centerY,
                         double X, double Y) {
  double scale_real = X / WIDTH;
  double scale_imag = Y / HEIGHT;

  for (int py = 0; py < HEIGHT; ++py) {
    for (int px = 0; px < WIDTH; ++px) {
      double real = centerX + (px - WIDTH / 2.0) * scale_real;
      double imag = centerY + (py - HEIGHT / 2.0) * scale_imag;

      std::complex<double> c(real, imag);
      std::complex<double> z(0.0, 0.0);
      int iter = 0;

      while (std::abs(z) <= 2.0 && iter < MAX_ITER) {
        z = z * z + c;
        ++iter;
      }

      int pixelIndex = (py * WIDTH + px) * COLOR_CHANNELS;

      // Simple color mapping based on iterations
      if (iter < MAX_ITER) {
        pixels[pixelIndex] = iter % 256;           // Red channel
        pixels[pixelIndex + 1] = (iter * 2) % 256; // Green channel
        pixels[pixelIndex + 2] = (iter * 3) % 256; // Blue channel
        pixels[pixelIndex + 3] = 255;              // Alpha channel
      } else {
        // Mandelbrot set (black)
        pixels[pixelIndex] = 0;
        pixels[pixelIndex + 1] = 0;
        pixels[pixelIndex + 2] = 0;
        pixels[pixelIndex + 3] = 255;
      }
    }
  }
}

int main() {
  // Initialize pixel array
  sf::Uint8 *pixels = new sf::Uint8[WIDTH * HEIGHT * COLOR_CHANNELS];

  // Example CENTER and size for the viewport
  double centerX = -0.0;
  double centerY = -0.0;
  double X = 3.0; // Width of the viewport in the complex plane
  double Y = 2.0; // Height of the viewport in the complex plane

  double currentZoom = 1;

  // Calculate Mandelbrot
  calculateMandelbrot(pixels, centerX, centerY, X, Y);

  // Display using SFML
  sf::Texture texture;
  texture.create(WIDTH, HEIGHT);
  texture.update(pixels);

  sf::Sprite sprite(texture);
  sprite.setOrigin(WIDTH / 2.0, HEIGHT / 2.0);
  sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Mandelbrot Fractal");
  sf::View view;
  view.reset(sf::FloatRect(0, 0, WIDTH, HEIGHT));
  window.setFramerateLimit(30);

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        window.close();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
      view.move(0, -MOVE_SPEED * currentZoom);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
      view.move(0, MOVE_SPEED * currentZoom);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
      view.move(-MOVE_SPEED * currentZoom, 0);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
      view.move(MOVE_SPEED * currentZoom, 0);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
      currentZoom *= 1 + ZOOM_LEVEL;
      view.zoom(1 + ZOOM_LEVEL);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
      currentZoom *= 1 - ZOOM_LEVEL;
      view.zoom(1 - ZOOM_LEVEL);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
      centerX = (view.getCenter().x - WIDTH / 2.0) * X / WIDTH;
      centerY = (view.getCenter().y - HEIGHT / 2.0) * Y / HEIGHT;
      calculateMandelbrot(pixels, centerX, centerY, X * currentZoom,
                          Y * currentZoom);
      texture.update(pixels);
      sprite.setPosition(view.getCenter().x, view.getCenter().y);
      sprite.setScale(currentZoom, currentZoom);
    }

    window.clear();
    window.setView(view);
    window.draw(sprite);
    window.display();
  }

  delete[] pixels;
  return 0;
}
