#include "Renderer.hpp"

#include <raylib.h>


void drawGrid(const Grid& grid, int cellSize) {
    for(int y = 0; y < grid.height(); y++) {
        for(int x = 0; x < grid.width(); x++) {
            if(grid.hasSand(x, y)) {
                DrawRectangle(
                    x * cellSize,
                    y * cellSize,
                    cellSize,
                    cellSize,
                    grid.getColor(x, y)
                );
            }
        }
    }
}

void drawBrushPreview(const Grid& grid, int centerX, int centerY, int radius, int cellSize) {
    for(int dy = -radius; dy <= radius; dy++) {
        for(int dx = -radius; dx <= radius; dx++) {
            if(dx * dx + dy * dy > radius * radius) {
                continue;
            }

            int x = centerX + dx;
            int y = centerY + dy;

            if(!grid.isInside(x, y)) {
                continue;
            }

            DrawRectangle(
                x * cellSize,
                y * cellSize,
                cellSize,
                cellSize,
                LIGHTGRAY
            );
        }
    }
}