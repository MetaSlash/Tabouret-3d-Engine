#include "../Point/Point.hpp"

#ifndef TRIANGLE_H
#define TRIANGLE_H

class Triangle {
  private:
    uint32_t color;
    Point point[3];

  public:
    Triangle();
    Triangle(Point p1, Point p2, Point p3);
    Triangle(Point p1, Point p2, Point p3, uint32_t color);

    uint32_t getColor();
    Point* getPoints();

    void setP1(Point p);
    void setP2(Point p);
    void setP3(Point p);
};

#endif  // TRIANGLE_H