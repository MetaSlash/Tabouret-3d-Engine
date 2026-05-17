/**
 * Directory : src/Shapes/Line/Line.hpp
 * Author : Tabouret
 * Creation Date : 02/05/2026
 */

#ifndef LINE_H
#define LINE_H

#include <cstdint>

#include "../Point/Point.hpp"
#include "../Shapes.hpp"

class Line : public Shape {
  private:
    Point point[2];

  public:
    Line();
    Line(Point p1, Point p2);
    Line(Point p1, Point p2, uint32_t color);

    Point* getPoints();
    Type type() override;

    void setP1(Point p);
    void setP2(Point p);
};
#endif  // LINE_H