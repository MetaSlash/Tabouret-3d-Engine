cmake_minimum_required(VERSION 3.10)
project(SoftwareRenderer)

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)
FetchContent_Declare(
  SDL2
  GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
  GIT_TAG        release-2.28.x
)
FetchContent_MakeAvailable(SDL2)

# Include both .cpp files
add_executable(renderer 
    src/main.cpp

    src/Canvas/Canvas.cpp
    src/Shapes/Rectangle/Rectangle.cpp
    src/Shapes/Point/Point.cpp
    src/Shapes/Triangle/Triangle.cpp
    src/Shapes/Line/Line.cpp
    src/Shapes/Square/Square.cpp
    src/Shapes/Cuboid/Cuboid.cpp
    src/Shapes/Cuboid/McCuboid/McCuboid.cpp
)

target_link_libraries(renderer PRIVATE SDL2::SDL2-static SDL2::SDL2main)