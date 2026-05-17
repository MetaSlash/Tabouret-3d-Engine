/**
 * Directory : src/Shapes/Rectangle/Rectangle.hpp
 * Author : Tabouret
 * Creation Date : 27/04/2026
 */

#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <cstdint>

#include "../Shapes.hpp"

class Rectangle : public Shape {
  private:
    // Member variables
    int x, y;
    float xNorm, yNorm;
    int width, height;

    // Internal helper methods for coordinate conversion
    void deNormalizeX(void);
    void deNormalizeY(void);
    void xToNormalized(void);
    void yToNormalized(void);

  public:
    // Constructors
    Rectangle(int x, int y, int h, int w, uint32_t color);
    Rectangle(int x, int y, int z, int h, int w, uint32_t color);

    // Getters (const-qualified as per your .cpp)
    int getX(void) const;
    int getY(void) const;
    float getXNorm(void) const;
    float getYNorm(void) const;
    int getWidth(void) const;
    int getHeight(void) const;
    Type type() override;

    // Setters
    void setX(int newX);
    void setY(int newY);
    void setXNorm(float newX);
    void setYNorm(float newY);
    void setCoords(int newX, int newY);
    void setNormCoords(float newX, float newY);
    void setWidth(int newWidth);
    void setHeight(int newHeight);

    // 3D Projection method
    void set3dCoods(float newX, float newY, float newZ);
};

#endif  // RECTANGLE_H