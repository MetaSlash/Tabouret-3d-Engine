/**
 * Directory : src/Canvas.cpp
 * Author : Tabouret
 * Creation Date : 26/04/2026
 */

#include "Canvas.hpp"

#include <math.h>

#include <iostream>
#include <vector>

static const double PI = 3.14159265358979323846;

Canvas::Canvas(int w, int h, uint32_t c)
    : cWidth(w), cHeight(h), cColor(c), buffer(w * h, cColor) {}

// Transforms a world-space Point into screen coordinates using the camera.
// Returns false if the point is behind the camera (should not be drawn).
bool Canvas::project(Point p, Camera cam, int& outX, int& outY) {
    // Translate to camera-relative space
    double dx = p.getWorldX() - cam.x();
    double dy = p.getWorldY() - cam.y();
    double dz = p.getWorldZ() - cam.z();

    // Apply yaw rotation (around Y axis)
    double cosY = cos(cam.yaw());
    double sinY = sin(cam.yaw());
    double lx = dx * cosY - dz * sinY;
    double ly = dy;
    double lz = dx * sinY + dz * cosY;

    // Apply pitch rotation (around X axis)
    double cosP = cos(cam.pitch());
    double sinP = sin(cam.pitch());
    double finalX = lx;
    double finalY = ly * cosP - lz * sinP;
    double finalZ = ly * sinP + lz * cosP;

    if (finalZ <= 0.0) return false;

    double focalLen = 1.0 / tan(cam.fov() * 0.5 * PI / 180.0);
    double aspect = (double)cWidth / (double)cHeight;
    double xn = (finalX / finalZ) * focalLen / aspect;
    double yn = (finalY / finalZ) * focalLen;

    outX = (int)((xn + 1.0) * 0.5 * cWidth);
    outY = (int)((1.0 - (yn + 1.0) * 0.5) * cHeight);
    return true;
}

void Canvas::drawRectangle(Rectangle r, Camera cam) {
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

void Canvas::drawPoint(Point p, Camera cam) {
    int sx, sy;
    if (project(p, cam, sx, sy) && isCoordsValid(sx, sy))
        buffer[sy * cWidth + sx] = p.getColor();
}

void Canvas::drawLine(Line l, Camera cam) {
    // Bresenham's line algorithm
    // https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm
    int p1X, p1Y, p2X, p2Y;
    if (!project(l.getPoints()[0], cam, p1X, p1Y)) return;
    if (!project(l.getPoints()[1], cam, p2X, p2Y)) return;

    int dx = abs(p2X - p1X);
    int dy = -abs(p2Y - p1Y);
    int sx = (p1X < p2X) ? 1 : -1;
    int sy = (p1Y < p2Y) ? 1 : -1;
    int err = dx + dy;

    uint32_t color = l.getColor();
    while (true) {
        if (isCoordsValid(p1X, p1Y))
            buffer[p1Y * cWidth + p1X] = color;
        if (p1X == p2X && p1Y == p2Y) break;
        int e2 = 2 * err;
        if (e2 >= dy) { err += dy; p1X += sx; }
        if (e2 <= dx) { err += dx; p1Y += sy; }
    }
}

void Canvas::drawTriangle(Triangle t, Camera cam) {
    for (size_t i = 0; i < 3; i++) {
        drawLine(
            Line(t.getPoints()[i], t.getPoints()[(i + 1) % 3], t.getColor()),
            cam);
    }
}

void Canvas::drawTriangle(Triangle t, uint32_t color, Camera cam) {
    for (size_t i = 0; i < 3; i++) {
        drawLine(Line(t.getPoints()[i], t.getPoints()[(i + 1) % 3], color),
                 cam);
    }
}

void Canvas::drawSquare(Square s, Camera cam) {
    for (size_t i = 0; i < 2; i++) {
        drawTriangle(s.getTriangle()[i], s.getColor(), cam);
    }
}
void Canvas::drawSquare(Square s, uint32_t color, Camera cam) {
    for (size_t i = 0; i < 2; i++) {
        drawTriangle(s.getTriangle()[i], color, cam);
    }
}

void Canvas::drawCuboid(Cuboid c, Camera cam) {
    for (size_t i = 0; i < 6; i++) {
        drawSquare(c.getSquares()[i], c.getColor(), cam);
    }
}

void Canvas::clear(void) { std::fill(buffer.begin(), buffer.end(), cColor); }

void Canvas::draw(Shape* s, Camera cam) {
    switch (s->type()) {
        case (Type::cuboid):
            drawCuboid(*static_cast<Cuboid*>(s), cam);
            break;

        case (Type::line):
            drawLine(*static_cast<Line*>(s), cam);
            break;

        case (Type::point):
            drawPoint(*static_cast<Point*>(s), cam);
            break;

        case (Type::rectangle):
            drawRectangle(*static_cast<Rectangle*>(s), cam);
            break;

        case (Type::square):
            drawSquare(*static_cast<Square*>(s), cam);
            break;

        case (Type::triangle):
            drawTriangle(*static_cast<Triangle*>(s), cam);
            break;

        default:
            break;
    }
}

bool Canvas::isCoordsValid(int px, int py) {
    return (px >= 0 && px < cWidth && py >= 0 && py < cHeight);
}