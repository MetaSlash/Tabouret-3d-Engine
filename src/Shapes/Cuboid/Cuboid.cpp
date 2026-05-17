/**
 * Directory : src/Shapes/Cuboid/Cuboid.cpp
 * Author : Tabouret
 * Creation Date : 03/05/2026
 */

#include "Cuboid.hpp"

#include <iostream>

Cuboid::Cuboid() {
    color = 0xFFFFFFFF;
    square[0] = Square();
    square[1] = Square();
    square[2] = Square();
    square[3] = Square();
    square[4] = Square();
    square[5] = Square();
}
Cuboid::Cuboid(Square s1, Square s2, Square s3, Square s4, Square s5,
               Square s6) {
    color = 0xFFFFFFFF;
    square[0] = s1;
    square[1] = s2;
    square[2] = s3;
    square[3] = s4;
    square[4] = s5;
    square[5] = s6;
}
Cuboid::Cuboid(Square s1, Square s2, Square s3, Square s4, Square s5, Square s6,
               uint32_t color) {
    this->color = color;
    square[0] = s1;
    square[1] = s2;
    square[2] = s3;
    square[3] = s4;
    square[4] = s5;
    square[5] = s6;
}

Cuboid::Cuboid(Point p1, Point p2, Point p3, Point p4, Point p5, Point p6,
               Point p7, Point p8) {
    color = 0xFFFFFFFF;
    square[0] = Square(p1, p2, p3, p4);
    square[1] = Square(p5, p1, p4, p8);
    square[2] = Square(p5, p6, p7, p8);
    square[3] = Square(p2, p4, p7, p3);
    square[4] = Square(p1, p5, p4, p2);
    square[5] = Square(p4, p8, p7, p3);
}
Cuboid::Cuboid(Point p1, Point p2, Point p3, Point p4, Point p5, Point p6,
               Point p7, Point p8, uint32_t color) {
    this->color = color;
    square[0] = Square(p1, p2, p3, p4);  // Front
    square[1] = Square(p5, p1, p4, p8);  // Left
    square[2] = Square(p6, p7, p8, p5);  // Back
    square[3] = Square(p2, p6, p7, p3);  // Right
    square[4] = Square(p1, p5, p6, p2);  // Top
    square[5] = Square(p4, p8, p7, p3);  // Bot
}

// This constructor assume that the cube have a size of 1
Cuboid::Cuboid(int x, int y, int z) {
    point.setWorldX(x);
    point.setWorldY(y);
    point.setWorldZ(z);
    color = 0xFFFFFFFF;
    Point p[8];
    p[1] = Point(-0.5 + x, 0.5 + y, -0.5 + z);
    p[2] = Point(0.5 + x, 0.5 + y, -0.5 + z);
    p[3] = Point(0.5 + x, -0.5 + y, -0.5 + z);
    p[4] = Point(-0.5 + x, -0.5 + y, -0.5 + z);

    p[5] = Point(-0.5 + x, 0.5 + y, 0.5 + z);
    p[6] = Point(0.5 + x, 0.5 + y, 0.5 + z);
    p[7] = Point(0.5 + x, -0.5 + y, 0.5 + z);
    p[8] = Point(-0.5 + x, -0.5 + y, 0.5 + z);

    square[0] = Square(p[1], p[2], p[3], p[4]);  // Front
    square[1] = Square(p[5], p[1], p[4], p[8]);  // Left
    square[2] = Square(p[6], p[7], p[8], p[5]);  // Back
    square[3] = Square(p[2], p[6], p[7], p[3]);  // Right
    square[4] = Square(p[1], p[5], p[6], p[2]);  // Top
    square[5] = Square(p[4], p[8], p[7], p[3]);  // Bot
}

// This constructor assume that the cube have a size of 1
Cuboid::Cuboid(int x, int y, int z, uint32_t color) {
    point.setWorldX(x);
    point.setWorldY(y);
    point.setWorldZ(z);
    this->color = color;
    Point p[8];
    p[1] = Point(-0.5 + x, 0.5 + y, -0.5 + z);
    p[2] = Point(0.5 + x, 0.5 + y, -0.5 + z);
    p[3] = Point(0.5 + x, -0.5 + y, -0.5 + z);
    p[4] = Point(-0.5 + x, -0.5 + y, -0.5 + z);

    p[5] = Point(-0.5 + x, 0.5 + y, 0.5 + z);
    p[6] = Point(0.5 + x, 0.5 + y, 0.5 + z);
    p[7] = Point(0.5 + x, -0.5 + y, 0.5 + z);
    p[8] = Point(-0.5 + x, -0.5 + y, 0.5 + z);

    square[0] = Square(p[1], p[2], p[3], p[4]);  // Front
    square[1] = Square(p[5], p[1], p[4], p[8]);  // Left
    square[2] = Square(p[6], p[7], p[8], p[5]);  // Back
    square[3] = Square(p[2], p[6], p[7], p[3]);  // Right
    square[4] = Square(p[1], p[5], p[6], p[2]);  // Top
    square[5] = Square(p[4], p[8], p[7], p[3]);  // Bot
}

void Cuboid::setIntCoords(int x, int y, int z) {
    point.setWorldX((long)x);
    point.setWorldY((long)y);
    point.setWorldZ((long)z);

    Point p[8];
    p[1] = Point(-0.5 + x, 0.5 + y, -0.5 + z);
    p[2] = Point(0.5 + x, 0.5 + y, -0.5 + z);
    p[3] = Point(0.5 + x, -0.5 + y, -0.5 + z);
    p[4] = Point(-0.5 + x, -0.5 + y, -0.5 + z);

    p[5] = Point(-0.5 + x, 0.5 + y, 0.5 + z);
    p[6] = Point(0.5 + x, 0.5 + y, 0.5 + z);
    p[7] = Point(0.5 + x, -0.5 + y, 0.5 + z);
    p[8] = Point(-0.5 + x, -0.5 + y, 0.5 + z);

    square[0] = Square(p[1], p[2], p[3], p[4]);  // Front
    square[1] = Square(p[5], p[1], p[4], p[8]);  // Left
    square[2] = Square(p[6], p[7], p[8], p[5]);  // Back
    square[3] = Square(p[2], p[6], p[7], p[3]);  // Right
    square[4] = Square(p[1], p[5], p[6], p[2]);  // Top
    square[5] = Square(p[4], p[8], p[7], p[3]);  // Bot
}

Square* Cuboid::getSquares() { return square; }

Point Cuboid::getPointCoords() { return point; }

Type Cuboid::type() { return Type::cuboid; }

void Cuboid::showIntCoords() {
    std::cout << "x: " << this->getPointCoords().getWorldX()
              << "  y: " << this->getPointCoords().getWorldY()
              << "  z: " << this->getPointCoords().getWorldZ() << std::endl;
}
