/**
 * Directory : src/Shapes/Point/Point.hpp
 * Author : Tabouret
 * Creation Date : 27/04/2026
 */

#ifndef POINT_H
#define POINT_H

#include <cstdint>

#include "../Shape/Shape.hpp"

class Point : public Shape {
  private:
    // Member variables
    double worldX, worldY, worldZ;
    double xNorm, yNorm;
    int screenX, screenY;

    void update3dCoods(void);

  public:
    // Constructors
    Point();
    Point(double newScreenX, double newScreenY, uint32_t color);
    Point(double x, double y, double z);
    Point(double x, double y, double z, uint32_t color);

    // Getters (const-qualified as per your .cpp)
    int getScreenX(void) const;
    int getScreenY(void) const;
    Type type() override;

    double getWorldX(void) const;
    double getWorldY(void) const;
    double getWorldZ(void) const;

    // Setters
    void setWorldX(double newX);
    void setWorldY(double newY);
    void setWorldZ(double newZ);

    // 3D Projection method
};

#endif  // RECTANGLE_H