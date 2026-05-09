/**
 * Directory : src/Shapes/Point/Point.cpp
 * Author : Tabouret
 * Creation Date : 27/04/2026
 */

#include "Point.hpp"

#include "../../constants.hpp"

// Constructor
Point::Point() {
    color = 0xFFFFFFFF;

    worldX = 0;
    worldY = 0;
    worldZ = 0;
    update3dCoods();
}

// DO NOT USE IN NORMAL CODE
Point::Point(double newScreenX, double newScreenY, uint32_t color) {
    screenX = newScreenX;
    screenY = newScreenY;

    this->color = color;
    worldX = 0;
    worldY = 0;
    worldZ = 0;
    xNorm = 0;
    yNorm = 0;
}

Point::Point(double x, double y, double z) {
    this->color = 0xFFFFFFFF;

    worldX = x;
    worldY = y;
    worldZ = z;
    update3dCoods();
}

Point::Point(double x, double y, double z, uint32_t color) {
    this->color = color;

    worldX = x;
    worldY = y;
    worldZ = z;
    update3dCoods();
}

int Point::getScreenX(void) const { return this->screenX; }
int Point::getScreenY(void) const { return this->screenY; }

double Point::getWorldX(void) const { return this->worldX; }
double Point::getWorldY(void) const { return this->worldY; }
double Point::getWorldZ(void) const { return this->worldZ; }

uint32_t Point::getColor(void) const { return this->color; }

// Setters
void Point::setWorldX(double newX) {
    worldX = newX;
    update3dCoods();
}
void Point::setWorldY(double newY) {
    worldY = newY;
    update3dCoods();
}
void Point::setWorldZ(double newZ) {
    worldZ = newZ;
    update3dCoods();
}

void Point::setColor(uint32_t newColor) { color = newColor; }

// Datas has to be normalize (between 0 and 1)

void Point::update3dCoods() {
    if (worldZ == 0) return;

    xNorm = worldX / worldZ;
    yNorm = worldY / worldZ;

    screenX = static_cast<int>((xNorm + 1.0) / 2.0 * WINDOW_WIDTH);
    screenY = static_cast<int>((1 - (yNorm + 1.0) / 2.0) * WINDOW_HEIGHT);
}
