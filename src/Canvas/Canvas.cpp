/**
 * Directory : src/Canvas.cpp
 * Author : Tabouret
 * Creation Date : 26/04/2026
 */

#include "Canvas.hpp"

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

    plotLine(x0, y0, x1, y1)
        dx = abs(x1 - x0)
        sx = x0 < x1 ? 1 : -1
        dy = -abs(y1 - y0)
        sy = y0 < y1 ? 1 : -1
        error = dx + dy

        while true
            plot(x0, y0)
            e2 = 2 * error
            if e2 >= dy
                if x0 == x1 break
                error = error + dy
                x0 = x0 + sx
            end if
            if e2 <= dx
                if y0 == y1 break
                error = error + dx
                y0 = y0 + sy
            end if
        end while
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
    for (pt p : points) {
        drawPoint(Point(p.x, p.y, l.getColor()));
    }
}

void Canvas::drawTriangle(Triangle t) {
    for (size_t i = 0; i < 3; i++) {
        drawLine(
            Line(t.getPoints()[i], t.getPoints()[(i + 1) % 3], t.getColor()));
    }
}

void Canvas::drawTriangle(Triangle t, uint32_t color) {
    for (size_t i = 0; i < 3; i++) {
        drawLine(Line(t.getPoints()[i], t.getPoints()[(i + 1) % 3], color));
    }
}

void Canvas::drawSquare(Square s) {
    for (size_t i = 0; i < 2; i++) {
        drawTriangle(s.getTriangle()[i], s.getColor());
    }
}
void Canvas::drawSquare(Square s, uint32_t color) {
    for (size_t i = 0; i < 2; i++) {
        drawTriangle(s.getTriangle()[i], color);
    }
}

void Canvas::drawCuboid(Cuboid c) {
    for (size_t i = 0; i < 6; i++) {
        drawSquare(c.getSquares()[i], c.getColor());
    }
}

void Canvas::clear(void) { std::fill(buffer.begin(), buffer.end(), cColor); }

void Canvas::draw(Shape* s) {
    switch (s->type()) {
        case (Type::cuboid):
            drawCuboid(*static_cast<Cuboid*>(s));
            break;

        case (Type::line):
            drawLine(*static_cast<Line*>(s));
            break;

        case (Type::point):
            drawPoint(*static_cast<Point*>(s));
            break;

        case (Type::rectangle):
            drawRectangle(*static_cast<Rectangle*>(s));
            break;

        case (Type::square):
            drawSquare(*static_cast<Square*>(s));
            break;

        case (Type::triangle):
            drawTriangle(*static_cast<Triangle*>(s));
            break;

        default:
            break;
    }
}

bool Canvas::isCoordsValid(int px, int py) {
    return (px >= 0 && px < cWidth && py >= 0 && py < cHeight);
}