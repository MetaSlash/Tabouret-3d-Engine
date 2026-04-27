#include "Canvas.h"

#include <iostream>

void Canvas::drawRectangle(Rectangle& r) {
    for (int row = r.getHeight() / 2 * -1; row < r.getHeight() / 2; ++row) {
        for (int col = r.getWidth() / 2 * -1; col < r.getWidth() / 2; ++col) {
            int drawX = r.getX() + col;
            int drawY = r.getY() + row;
            if (drawX >= 0 && drawX < cWidth && drawY >= 0 && drawY < cHeight) {
                buffer[drawY * cWidth + drawX] = r.getColor();
            }
        }
    }
}

void Canvas::clear(void) { std::fill(buffer.begin(), buffer.end(), cColor); }

Canvas::Canvas(int w, int h, uint32_t c)
    : cWidth(w), cHeight(h), cColor(c), buffer(w * h, cColor) {}