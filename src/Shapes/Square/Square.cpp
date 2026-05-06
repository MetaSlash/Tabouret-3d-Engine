#include "./Square.hpp"

#include <cstdlib>
#include <iostream>

// Constructors
Square::Square() {
    color = 0xFFFFFFFF;
    triangle[0] = Triangle(Point(), Point(), Point());
    triangle[1] = Triangle(Point(), Point(), Point());
}

Square::Square(Triangle t1, Triangle t2) {
    color = 0xFFFFFFFF;
    if (squareValid(t1, t2)) {
        triangle[0] = t1;
        triangle[1] = t2;
    } else {
        std::cerr << "Triangles given in a square don't have 2 points in comon"
                  << std::endl;
        std::exit(1);
    }
}
Square::Square(Triangle t1, Triangle t2, uint32_t color) {
    this->color = color;
    if (squareValid(t1, t2)) {
        triangle[0] = t1;
        triangle[1] = t2;
    } else {
        std::cerr << "Triangles given in a square don't have 2 points in comon"
                  << std::endl;
        std::exit(1);
    }
}

// https://imgur.com/a/kN6lCrc
// Corresponding points of the 2 triangles must be p1 and p3
Square::Square(Point p1, Point p2, Point p3, Point p4) {
    color = 0xFFFFFFFF;
    triangle[0] = Triangle(p1, p3, p2, color);
    triangle[1] = Triangle(p1, p3, p4, color);
}
Square::Square(Point p1, Point p2, Point p3, Point p4, uint32_t color) {
    this->color = color;
    triangle[0] = Triangle(p1, p3, p2, color);
    triangle[1] = Triangle(p1, p3, p4, color);
}

// Getter
Triangle* Square::getTriangle() { return triangle; }
uint32_t Square::getColor() { return color; }

// Cool Methods

bool Square::squareValid(Triangle t1, Triangle t2) {
    int count = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (pointsEquale(t1.getPoints()[i], t2.getPoints()[j])) {
                count++;
            }
        }
    }
    return count == 2;
}

bool Square::pointsEquale(Point p1, Point p2) {
    return p1.getWorldX() == p2.getWorldX() &&
           p1.getWorldY() == p2.getWorldY() && p1.getWorldZ() == p2.getWorldZ();
}
