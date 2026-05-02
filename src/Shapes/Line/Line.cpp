#include "Line.h"
Line::Line() {
    point[0] = Point();
    point[1] = Point();
    color = 0xFFFFFFFF;  // Defalut color as white
}

Line::Line(Point p1, Point p2) {
    point[0] = p1;
    point[1] = p2;
    color = 0xFFFFFFFF;  // Defalut color as white
}

Line::Line(Point p1, Point p2, uint32_t color) {
    point[0] = p1;
    point[1] = p2;
    this->color = color;  // Defalut color as white
}

uint32_t Line::getColor() { return color; }
Point* Line::getPoints() { return point; }

void Line::setP1(Point p) { point[0] = p; }
void Line::setP2(Point p) { point[1] = p; }