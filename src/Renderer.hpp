#pragma once

#include "Grid.hpp"

void drawGrid(
    const Grid& grid,
    int cellSize
);

void drawBrushPreview(
    const Grid& grid,
    int centerX,
    int centerY,
    int radius,
    int cellSize
);