#ifndef SHAPE_H
#define SHAPE_H

#include <cstdint>

enum Type { mcCuboid, cuboid, line, point, rectangle, square, triangle };

class Shape {
  protected:
    uint32_t color;

  public:
    // Constructors
    Shape();
    Shape(uint32_t color);

    // Setters
    void setColor(uint32_t color);

    virtual Type type() = 0;

    // Getters
    uint32_t getColor();
};

#endif  // SHAPES_H