#include "Point.h"

#include "../../constants.h"

// Constructor
Point::Point(double x, double y, double z) {
    setColor(0xFFFFFFFF);

    setX(x);
    setY(y);
    setZ(z);
    update3dCoods();
}

Point::Point(double x, double y, double z, uint32_t color) {
    setColor(color);

    setX(x);
    setY(y);
    setZ(z);
    update3dCoods();
}

double Point::getX(void) const { return this->x; }
double Point::getY(void) const { return this->y; }
double Point::getZ(void) const { return this->z; }

double Point::getXNorm(void) const { return this->xNorm; }
double Point::getYNorm(void) const { return this->yNorm; }

uint32_t Point::getColor(void) const { return this->color; }

// Setters
void Point::setX(double newX) {
    x = newX;
    xToNormalized();
}
void Point::setY(double newY) {
    y = newY;
    yToNormalized();
}
void Point::setZ(double newZ) {
    z = newZ;
    update3dCoods();
}

void Point::setXNorm(double newX) {
    xNorm = newX;
    deNormalizeX();
}

void Point::setYNorm(double newY) {
    yNorm = newY;
    deNormalizeY();
}

void Point::setCoords(double newX, double newY) {
    setX(newX);
    setY(newY);
}

void Point::setNormCoords(double newX, double newY) {
    setXNorm(newX);
    setYNorm(newY);
}

void Point::setColor(uint32_t newColor) { color = newColor; }

// Cool Methods
void Point::deNormalizeX(void) { x = (xNorm + 1) / 2 * WINDOW_WIDTH; }
void Point::deNormalizeY(void) { y = (1 - (yNorm + 1) / 2) * WINDOW_HEIGHT; }

void Point::xToNormalized(void) {
    xNorm = (static_cast<double>(x) / (WINDOW_WIDTH / 2.0f)) - 1.0f;
}

void Point::yToNormalized(void) {
    yNorm = (static_cast<double>(y) / (WINDOW_HEIGHT / 2.0f)) - 1.0f;
}

// Datas has to be normalize (between 0 and 1)
void Point::set3dCoods(double newX, double newY, double newZ) {
    setXNorm(newX / newZ);
    setYNorm(newY / newZ);
}

void Point::update3dCoods() {
    setXNorm(this->x / this->z);
    setYNorm(this->y / this->z);
}
