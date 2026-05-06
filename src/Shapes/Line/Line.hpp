#include <cstdint>

#include "../Point/Point.hpp"

#ifndef LINE_H
#define LINE_H

class Line {
  private:
    uint32_t color;
    Point point[2];

  public:
    Line();
    Line(Point p1, Point p2);
    Line(Point p1, Point p2, uint32_t color);

    uint32_t getColor();
    Point* getPoints();

    void setP1(Point p);
    void setP2(Point p);
};
#endif  // LINE_H