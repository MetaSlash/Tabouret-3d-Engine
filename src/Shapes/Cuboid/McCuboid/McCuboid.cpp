/**
 * @file McCuboid.cpp
 * @details src\Shapes\Cuboid\McCuboid\McCuboid.cpp
 *
 * @author Tabouret
 * @date 06/05/2026
 */

#include "McCuboid.hpp"

McCuboid::McCuboid() {
    x = 0;
    y = 0;
    z = 0;
}

McCuboid::McCuboid(int x, int y, int z) {}

Type McCuboid::type() { return Type::mcCuboid; }
