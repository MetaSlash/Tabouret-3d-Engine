#include "Canvas.h"

#include <math.h>

#include <iostream>
#include <vector>

Canvas::Canvas(int w, int h, uint32_t c)
    : cWidth(w), cHeight(h), cColor(c), buffer(w * h, cColor) {}

void Canvas::drawRectangle(Rectangle r) {
    for (int row = r.getHeight() / 2 * -1; row < r.getHeight() / 2; ++row) {
        for (int col = r.getWidth() / 2 * -1; col < r.getWidth() / 2; ++col) {
            int drawX = r.getX() + col;
            int drawY = r.getY() + row;
            if (drawX >= 0 && drawX < cWidth && drawY >= 0 && drawY < cHeight) {
                // Core Mecanic
                buffer[drawY * cWidth + drawX] = r.getColor();
            }
        }
    }
}

void Canvas::drawPoint(Point p) {
    if (isCoordsValid(p.getScreenX(), p.getScreenY())) {
        buffer[p.getScreenY() * cWidth + p.getScreenX()] = p.getColor();
    }
}

void Canvas::drawLine(Line l) {
    /* Algo from
     * https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm#Algorithm
    /*
    plotLine(x0, y0, x1, y1)
        dx = x1 - x0
        dy = y1 - y0
        D = 2*dy - dx
        y = y0

        for x from x0 to x1
            plot(x, y)
            if D > 0
                y = y + 1
                D = D + (2 * (dy - dx))
            else
                D = D + 2*dy
            end if
    */
    struct pt {
        int x;
        int y;
        pt(int pt1, int pt2) : x(pt1), y(pt2) {}
    };

    std::vector<pt> points;

    int p1X = l.getPoints()[0].getScreenX();
    int p1Y = l.getPoints()[0].getScreenY();

    int p2X = l.getPoints()[1].getScreenX();
    int p2Y = l.getPoints()[1].getScreenY();

    int dx = abs(p2X - p1X);
    int dy = -abs(p2Y - p1Y);

    int sx = (p1X < p2X) ? 1 : -1;
    int sy = (p1Y < p2Y) ? 1 : -1;
    int err = dx + dy;
    while (true) {
        points.push_back(pt(p1X, p1Y));
        if (p1X == p2X && p1Y == p2Y) break;

        int e2 = 2 * err;
        if (e2 >= dy) {
            err += dy;
            p1X += sx;
        }
        if (e2 <= dx) {
            err += dx;
            p1Y += sy;
        }
    }

    for (int i = 0; i < points.size(); i++) {
        if (isCoordsValid(points.at(i).x, points.at(i).y)) {
            buffer[points.at(i).y * cWidth + points.at(i).x] = l.getColor();
        }
    }
}

void Canvas::drawTriangle(Triangle t) {
    drawLine(Line(t.getPoints()[0], t.getPoints()[1], t.getColor()));
    drawLine(Line(t.getPoints()[1], t.getPoints()[2], t.getColor()));
    drawLine(Line(t.getPoints()[2], t.getPoints()[0], t.getColor()));
}

void Canvas::clear(void) { std::fill(buffer.begin(), buffer.end(), cColor); }

bool Canvas::isCoordsValid(int px, int py) {
    return (px >= 0 && px < cWidth && py >= 0 && py < cHeight);
}