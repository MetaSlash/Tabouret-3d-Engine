#ifndef CANVAS_H
#define CANVAS_H

#include <vector>

#include "../Shapes/Shapes.h"

class Canvas {
   public:
    std::vector<uint32_t> buffer;
    int cWidth;
    int cHeight;
    uint32_t cColor;

    // Constructor
    Canvas(int w, int h, uint32_t c);

    // Draw Methods
    void drawRectangle(Rectangle& r);
    void drawPoint(Point& r);

    void clear(void);
};

#endif  // CANVAS_H