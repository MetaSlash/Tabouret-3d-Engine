/**
 * Directory : src/Canvas.hpp
 * Author : Tabouret
 * Creation Date : 26/04/2026
 */

#ifndef CANVAS_H
#define CANVAS_H

#include <vector>

#include "../Shapes/Shapes.hpp"
#include "../Camera/Camera.hpp"

class Canvas {
  private:
    bool project(Point p, Camera cam, int& outX, int& outY);

    void drawRectangle(Rectangle r, Camera cam);
    void drawPoint(Point p, Camera cam);
    void drawLine(Line l, Camera cam);
    void drawTriangle(Triangle t, Camera cam);
    void drawTriangle(Triangle t, uint32_t color, Camera cam);
    void drawSquare(Square s, Camera cam);
    void drawSquare(Square s, uint32_t color, Camera cam);
    void drawCuboid(Cuboid c, Camera cam);

  public:
    std::vector<uint32_t> buffer;
    int cWidth;
    int cHeight;
    uint32_t cColor;

    // Constructor
    Canvas(int w, int h, uint32_t c);

    // Draw Methods

    void draw(Shape* s, Camera cam);

    bool isCoordsValid(int px, int py);

    void clear(void);
};

#endif  // CANVAS_H