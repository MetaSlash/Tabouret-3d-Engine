/**
 * Directory : src/Shapes/Triangle/Triangle.cpp
 * Author : Tabouret
 * Creation Date : 02/05/2026
 */

#include "Triangle.hpp"

Triangle::Triangle() {
    color = 0xFFFFFFFF;
    point[0] = Point();
    point[1] = Point();
    point[2] = Point();
}

Triangle::Triangle(Point p1, Point p2, Point p3) {
    color = 0xFFFFFFFF;
    point[0] = p1;
    point[1] = p2;
    point[2] = p3;
}

Triangle::Triangle(Point p1, Point p2, Point p3, uint32_t newColor) {
    color = newColor;
    point[0] = p1;
    point[1] = p2;
    point[2] = p3;
}

void Triangle::setP1(Point p) { point[0] = p; }
void Triangle::setP2(Point p) { point[1] = p; }
void Triangle::setP3(Point p) { point[2] = p; }

Point* Triangle::getPoints() { return point; }
uint32_t Triangle::getColor() { return color; }