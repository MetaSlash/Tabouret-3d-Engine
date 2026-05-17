/**
 * Directory : src/Shapes/Triangle/Triangle.hpp
 * Author : Tabouret
 * Creation Date : 02/05/2026
 */

#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "../Point/Point.hpp"

#include "../Shape/Shape.hpp"

class Triangle : public Shape {
  private:
    Point point[3];

  public:
    Triangle();
    Triangle(Point p1, Point p2, Point p3);
    Triangle(Point p1, Point p2, Point p3, uint32_t color);

    Point* getPoints();

    Type type() override;

    void setP1(Point p);
    void setP2(Point p);
    void setP3(Point p);
};

#endif  // TRIANGLE_H