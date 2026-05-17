/**
 * Directory : src/Canvas.hpp
 * Author : Tabouret
 * Creation Date : 26/04/2026
 */

#ifndef CANVAS_H
#define CANVAS_H

#include <vector>

#include "../Shapes/Shapes.hpp"

class Canvas {
  private:
    void drawRectangle(Rectangle r);
    void drawPoint(Point p);
    void drawLine(Line l);
    void drawTriangle(Triangle t);
    void drawTriangle(Triangle t, uint32_t color);
    void drawSquare(Square s);
    void drawSquare(Square s, uint32_t color);
    void drawCuboid(Cuboid c);

  public:
    std::vector<uint32_t> buffer;
    int cWidth;
    int cHeight;
    uint32_t cColor;

    // Constructor
    Canvas(int w, int h, uint32_t c);

    // Draw Methods

    void draw(Shape* s);

    bool isCoordsValid(int px, int py);

    void clear(void);
};

#endif  // CANVAS_H