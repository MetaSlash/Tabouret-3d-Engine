/**
 * Directory : src/Shapes/Square/Square.hpp
 * Author : Tabouret
 * Creation Date : 02/05/2026
 */

#ifndef SQUARE_H
#define SQUARE_H

#include "../Shape/Shape.hpp"
#include "../Triangle/Triangle.hpp"

class Square : public Shape {
  private:
    Triangle triangle[2];

    bool squareValid(Triangle t1, Triangle t2);
    bool pointsEquale(Point p1, Point p2);

  public:
    Square();
    Square(Triangle t1, Triangle t2);
    Square(Triangle t1, Triangle t2, uint32_t color);
    Square(Point p1, Point p2, Point p3, Point p4);
    Square(Point p1, Point p2, Point p3, Point p4, uint32_t color);

    Type type() override;

    Triangle* getTriangle();
};

#endif  // SQUARE_H