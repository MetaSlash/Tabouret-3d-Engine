#include "Rectangle.h"

#include "../../constants.h"

int Rectangle::getX(void) const { return this->x; }
int Rectangle::getY(void) const { return this->y; }
float Rectangle::getXNorm(void) const { return this->xNorm; }
float Rectangle::getYNorm(void) const { return this->yNorm; }
int Rectangle::getWidth(void) const { return this->width; }
int Rectangle::getHeight(void) const { return this->height; }
uint32_t Rectangle::getColor(void) const { return this->color; }

// Setters
void Rectangle::setX(int newX) {
    x = newX;
    xToNormalized();
}
void Rectangle::setY(int newY) {
    y = newY;
    yToNormalized();
}

void Rectangle::setXNorm(float newX) {
    xNorm = newX;
    deNormalizeX();
}

void Rectangle::setYNorm(float newY) {
    yNorm = newY;
    deNormalizeY();
}

void Rectangle::setCoords(int newX, int newY) {
    setX(newX);
    setY(newY);
}

void Rectangle::setNormCoords(float newX, float newY) {
    setXNorm(newX);
    setYNorm(newY);
}

void Rectangle::setWidth(int newWidth) { width = newWidth; }
void Rectangle::setHeight(int newHeight) { height = newHeight; }
void Rectangle::setColor(uint32_t newColor) { color = newColor; }

// Cool Methods
void Rectangle::deNormalizeX(void) { x = (xNorm + 1) / 2 * WINDOW_WIDTH; }
void Rectangle::deNormalizeY(void) {
    y = (1 - (yNorm + 1) / 2) * WINDOW_HEIGHT;
}

void Rectangle::xToNormalized(void) {
    xNorm = (static_cast<float>(x) / (WINDOW_WIDTH / 2.0f)) - 1.0f;
}

void Rectangle::yToNormalized(void) {
    yNorm = (static_cast<float>(y) / (WINDOW_HEIGHT / 2.0f)) - 1.0f;
}

void Rectangle::set3dCoods(float newX, float newY, float newZ) {
    setXNorm(newX / newZ);
    setYNorm(newY / newZ);
}

// Constructor
Rectangle::Rectangle(int x, int y, int h, int w, uint32_t color)
    : height(h), width(w), color(color) {
    setX(x);
    setY(y);
}

Rectangle::Rectangle(int x, int y, int z, int h, int w, uint32_t color)
    : height(h), width(w), color(color) {
    setX(x);
    setY(y);
    this->set3dCoods(x, y, z);
}
