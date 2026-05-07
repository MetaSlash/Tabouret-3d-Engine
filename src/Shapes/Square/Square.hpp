/**
 * Directory : src/Shapes/Square/Square.hpp
 * Author : Tabouret
 * Creation Date : 02/05/2026
 */

#include "../Triangle/Triangle.hpp"

#ifndef SQUARE_H
#define SQUARE_H

class Square {
  private:
    Triangle triangle[2];
    uint32_t color;

    bool squareValid(Triangle t1, Triangle t2);
    bool pointsEquale(Point p1, Point p2);

  public:
    Square();
    Square(Triangle t1, Triangle t2);
    Square(Triangle t1, Triangle t2, uint32_t color);
    Square(Point p1, Point p2, Point p3, Point p4);
    Square(Point p1, Point p2, Point p3, Point p4, uint32_t color);

    uint32_t getColor();
    Triangle* getTriangle();
};

#endif  // SQUARE_H