#include <raylib.h>

#include "Grid.hpp"

Color randomSandColor() {
    /*
    return Color{
        static_cast<unsigned char>(GetRandomValue(200,255)),
        static_cast<unsigned char>(GetRandomValue(150,200)),
        static_cast<unsigned char>(GetRandomValue(100,150)),
        255
    };
    */

    constexpr float hue = 42.0f;

    float saturation = static_cast<float>(GetRandomValue(55, 75) / 100.0f);
    float value = static_cast<float>(GetRandomValue(65, 90) / 100.0f);

    return ColorFromHSV(hue, saturation, value);
}

void paintSand(Grid& grid, int centerX, int centerY, int radius) {
    for(int dy = -radius; dy <= radius; dy++) {
        for(int dx = -radius; dx <= radius; dx++) {
            if(dx * dx + dy * dy > radius * radius) {
                continue;
            }

            int x = centerX + dx;
            int y = centerY + dy;

            if(grid.isInside(x, y)) {
                grid.setSand(x, y, randomSandColor());
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

int main()
{
    constexpr int screenWidth = 800;
    constexpr int screenHeight = 600;
    constexpr int cellSize = 4;

    int brushRadius = 1;

    Grid grid(
        screenWidth / cellSize,
        screenHeight / cellSize
    );

    InitWindow(screenWidth, screenHeight, "Falling Sand Simulation");

    SetTargetFPS(60);

    while (!WindowShouldClose()) {


        /*
        --------- UPDATE LOGIC ---------
        */

        Vector2 mousePosition = GetMousePosition();

        int mouseX = static_cast<int>(mousePosition.x) / cellSize;
        int mouseY = static_cast<int>(mousePosition.y) / cellSize;

        // User input
        if(IsKeyPressed(KEY_R)) {
            grid.clearGrid();
        }

        int key = GetCharPressed();
        while(key > 0) {
            if (key == '+') {
                brushRadius = std::min(5, brushRadius + 1);
            } else if (key == '-') {
                brushRadius = std::max(0, brushRadius - 1);
            }
            key = GetCharPressed();
        }


        // Handle mouse input
        if(IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            paintSand(grid, mouseX, mouseY, brushRadius);
        }

        // Update grid
        for(int y = grid.height() - 2; y >= 0; y--) {
            for(int x = 0; x < grid.width(); x++) {
                if(!grid.hasSand(x, y)) {
                    continue;
                }
                if(!grid.hasSand(x, y + 1)) {
                    grid.swapCells(x, y, x, y + 1);
                    continue;
                }
                if(x > 0 && !grid.hasSand(x - 1, y + 1)){
                    grid.swapCells(x, y, x - 1, y + 1);
                    continue;
                }
                if(x < grid.width() - 1 && !grid.hasSand(x + 1, y + 1)){
                    grid.swapCells(x, y, x + 1, y + 1);
                }
            }
        }

        /*
        --------- RENDERING ---------
        */
        BeginDrawing();

        ClearBackground(WHITE);

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

        // Brush preview
        drawBrushPreview(grid, mouseX, mouseY, brushRadius, cellSize);

        // Draw UI
        DrawText(TextFormat("[+]/[-] to increase/decrease Brushsize (%i)", brushRadius + 1), 10, 10, 20, DARKGRAY);
        DrawText("[R] to reset", 10, 30, 20, DARKGRAY);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}