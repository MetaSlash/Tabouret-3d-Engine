
#ifndef POINT_H
#define POINT_H

#include <cstdint>

class Point {
   private:
    // Member variables
    double x, y, z;
    double xNorm, yNorm;
    uint32_t color;

    // Internal helper methods for coordinate conversion
    void deNormalizeX(void);
    void deNormalizeY(void);
    void xToNormalized(void);
    void yToNormalized(void);

   public:
    // Constructors
    Point(double x, double y, double z);
    Point(double x, double y, double z, uint32_t color);

    // Getters (const-qualified as per your .cpp)
    double getX(void) const;
    double getY(void) const;
    double getZ(void) const;

    double getXNorm(void) const;
    double getYNorm(void) const;

    uint32_t getColor(void) const;

    // Setters
    void setX(double newX);
    void setY(double newY);
    void setZ(double newZ);

    void setXNorm(double newX);
    void setYNorm(double newY);

    void setColor(uint32_t newColor);

    void setCoords(double newX, double newY);
    void setNormCoords(double newX, double newY);

    // 3D Projection method
    void set3dCoods(double newX, double newY, double newZ);
    void update3dCoods(void);
};

#endif  // RECTANGLE_H
;