#include "./Shape.hpp"

Shape::Shape() { color = 0xFFFFFFFF; }

Shape::Shape(uint32_t color) : color(color) {}

void Shape::setColor(uint32_t color) { this->color = color; }

uint32_t Shape::getColor() { return color; }