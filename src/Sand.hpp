#pragma once

#include <raylib.h>

#include "Grid.hpp"

Color getSandColor(bool coloredSand, float& rainbowHue);

void paintSand(
    Grid& grid,
    int centerX,
    int centerY,
    int radius,
    Color color
);