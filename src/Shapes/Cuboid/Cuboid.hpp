/**
 * Directory : src/Shapes/Cuboid/Cuboid.hpp
 * Author : Tabouret
 * Creation Date : 03/05/2026
 */

#include "../Square/Square.hpp"

class Cuboid {
  private:
    Square square[6];
    uint32_t color;

  public:
    // Constructors
    Cuboid();

    Cuboid(Square s1, Square s2, Square s3, Square s4, Square s5, Square s6);
    Cuboid(Square s1, Square s2, Square s3, Square s4, Square s5, Square s6,
           uint32_t color);

    Cuboid(Point p1, Point p2, Point p3, Point p4, Point p5, Point p6, Point p7,
           Point p8);
    Cuboid(Point p1, Point p2, Point p3, Point p4, Point p5, Point p6, Point p7,
           Point p8, uint32_t color);

    Cuboid(int x, int y, int z);
    Cuboid(int x, int y, int z, uint32_t color);

    // Setters
    void setIntCoords(int x, int y, int z);

    // Getters
    Square* getSquares();
    uint32_t getColor();
};