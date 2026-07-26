/**
 * Directory : src/Canvas.cpp
 * Author : Tabouret
 * Creation Date : 26/04/2026
 */

#include "Canvas.hpp"
#include "../constants.hpp"

#include <math.h>

#include <algorithm>
#include <iostream>
#include <limits>
#include <vector>

static const double PI = 3.14159265358979323846;

Canvas::Canvas(int w, int h, uint32_t c)
    : cWidth(w), cHeight(h), cColor(c),
      buffer(w * h, cColor),
      zBuffer(w * h, std::numeric_limits<double>::infinity()),
      wireframe(WIREFRAME_DEFAULT) {}

bool Canvas::project(Point p, Camera cam, int& outX, int& outY) {
    double z;
    return project(p, cam, outX, outY, z);
}

// Full projection — also outputs camera-space Z for depth interpolation.
bool Canvas::project(Point p, Camera cam, int& outX, int& outY, double& outZ) {
    double dx = p.getWorldX() - cam.x();
    double dy = p.getWorldY() - cam.y();
    double dz = p.getWorldZ() - cam.z();

    double cosY = cos(cam.yaw());
    double sinY = sin(cam.yaw());
    double lx = dx * cosY - dz * sinY;
    double ly = dy;
    double lz = dx * sinY + dz * cosY;

    double cosP = cos(cam.pitch());
    double sinP = sin(cam.pitch());
    double finalX = lx;
    double finalY = ly * cosP - lz * sinP;
    double finalZ = ly * sinP + lz * cosP;

    if (finalZ <= 0.0) return false;

    double focalLen = 1.0 / tan(cam.fov() * 0.5 * PI / 180.0);
    double aspect   = (double)cWidth / (double)cHeight;
    double xn = (finalX / finalZ) * focalLen / aspect;
    double yn = (finalY / finalZ) * focalLen;

    outX = (int)((xn + 1.0) * 0.5 * cWidth);
    outY = (int)((1.0 - (yn + 1.0) * 0.5) * cHeight);
    outZ = finalZ;
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

void Canvas::drawLineScreen(int x0, int y0, int x1, int y1, uint32_t color) {
    int dx = abs(x1 - x0), dy = -abs(y1 - y0);
    int sx = (x0 < x1) ? 1 : -1, sy = (y0 < y1) ? 1 : -1;
    int err = dx + dy;
    while (true) {
        if (isCoordsValid(x0, y0)) buffer[y0 * cWidth + x0] = color;
        if (x0 == x1 && y0 == y1) break;
        int e2 = 2 * err;
        if (e2 >= dy) { err += dy; x0 += sx; }
        if (e2 <= dx) { err += dx; y0 += sy; }
    }
}

void Canvas::drawLine(Line l, Camera cam) {
    // Bresenham's line algorithm
    // https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm
    int p1X, p1Y, p2X, p2Y;
    if (!project(l.getPoints()[0], cam, p1X, p1Y)) return;
    if (!project(l.getPoints()[1], cam, p2X, p2Y)) return;
    drawLineScreen(p1X, p1Y, p2X, p2Y, l.getColor());
}

// Fills a triangle with the given color using barycentric rasterization.
// Uses the z-buffer to resolve depth between overlapping triangles.
void Canvas::drawTriangle(Triangle t, uint32_t color, Camera cam) {
    int x0, y0, x1, y1, x2, y2;
    double z0, z1, z2;

    if (!project(t.getPoints()[0], cam, x0, y0, z0)) return;
    if (!project(t.getPoints()[1], cam, x1, y1, z1)) return;
    if (!project(t.getPoints()[2], cam, x2, y2, z2)) return;

    if (wireframe) {
        drawLineScreen(x0, y0, x1, y1, color);
        drawLineScreen(x1, y1, x2, y2, color);
        drawLineScreen(x2, y2, x0, y0, color);
        return;
    }

    int minX = std::max(0,          std::min({x0, x1, x2}));
    int maxX = std::min(cWidth - 1, std::max({x0, x1, x2}));
    int minY = std::max(0,          std::min({y0, y1, y2}));
    int maxY = std::min(cHeight - 1,std::max({y0, y1, y2}));

    // Signed area of the triangle in screen space (doubled).
    // Determines winding and is used to normalize barycentric weights.
    int area = (x1 - x0) * (y2 - y0) - (x2 - x0) * (y1 - y0);
    if (area == 0) return;

    for (int y = minY; y <= maxY; y++) {
        for (int x = minX; x <= maxX; x++) {
            // Barycentric weights: λ0 is the weight of vertex 0, etc.
            // Each is the signed area of the sub-triangle opposite to that vertex.
            int l0 = (x2 - x1) * (y - y1) - (y2 - y1) * (x - x1);
            int l1 = (x0 - x2) * (y - y2) - (y0 - y2) * (x - x2);
            int l2 = (x1 - x0) * (y - y0) - (y1 - y0) * (x - x0);

            // Point is inside when all weights have the same sign as area.
            if (area > 0) { if (l0 < 0 || l1 < 0 || l2 < 0) continue; }
            else           { if (l0 > 0 || l1 > 0 || l2 > 0) continue; }

            // Interpolate camera-space Z and depth-test.
            double z = ((double)l0 * z0 + (double)l1 * z1 + (double)l2 * z2) / area;
            int idx = y * cWidth + x;
            if (z < zBuffer[idx]) {
                zBuffer[idx] = z;
                buffer[idx]  = color;
            }
        }
    }
}

// Fills a triangle with the per-channel average color of its 3 vertices.
void Canvas::drawTriangle(Triangle t, Camera cam) {
    auto ch = [](uint32_t c, int shift) -> uint32_t { return (c >> shift) & 0xFF; };
    uint32_t c0 = t.getPoints()[0].getColor();
    uint32_t c1 = t.getPoints()[1].getColor();
    uint32_t c2 = t.getPoints()[2].getColor();
    uint32_t color =
        (((ch(c0,24) + ch(c1,24) + ch(c2,24)) / 3) << 24) |
        (((ch(c0,16) + ch(c1,16) + ch(c2,16)) / 3) << 16) |
        (((ch(c0, 8) + ch(c1, 8) + ch(c2, 8)) / 3) <<  8) |
        (  ch(c0, 0) + ch(c1, 0) + ch(c2, 0)) / 3;
    drawTriangle(t, color, cam);
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

void Canvas::clear(void) {
    std::fill(buffer.begin(),  buffer.end(),  cColor);
    std::fill(zBuffer.begin(), zBuffer.end(), std::numeric_limits<double>::infinity());
}

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