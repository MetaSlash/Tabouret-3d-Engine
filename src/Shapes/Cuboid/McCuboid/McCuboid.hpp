/**
 * Directory : src/Shapes/Cuboid/McCuboid/McCuboid.hpp
 * Author : Tabouret
 * Creation Date : 06/05/2026
 */

#include "../Cuboid.hpp"

class McCuboid : Cuboid {
  private:
    int x, y, z;

  public:
    McCuboid();
    McCuboid(int x, int y, int z);
};