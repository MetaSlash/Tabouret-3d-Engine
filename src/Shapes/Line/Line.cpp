/**
 * Directory : src/Shapes/Line/Line.cpp
 * Author : Tabouret
 * Creation Date : 02/05/2026
 */

#include "Line.hpp"

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

Type Line::type() { return Type::line; }

Point* Line::getPoints() { return point; }

void Line::setP1(Point p) { point[0] = p; }
void Line::setP2(Point p) { point[1] = p; }