#include <raylib.h>

#include "Grid.hpp"
#include "Renderer.hpp"
#include "Sand.hpp"

int main()
{
    constexpr int screenWidth = 800;
    constexpr int screenHeight = 600;
    constexpr int cellSize = 4;

    int brushRadius = 1;

    bool coloredSand = false;
    float rainbowHue = 0.0f;

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

        if(IsKeyPressed(KEY_C)) {
            coloredSand = !coloredSand;
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
            Color sandColor = getSandColor(coloredSand, rainbowHue);

            paintSand(grid, mouseX, mouseY, brushRadius, sandColor);
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

        // Draw grid
        drawGrid(grid, cellSize);

        // Brush preview
        drawBrushPreview(grid, mouseX, mouseY, brushRadius, cellSize);

        // Draw UI
        DrawFPS(screenWidth - 80, 10);
        DrawText(TextFormat("[+]/[-] to increase/decrease Brushsize (%i)", brushRadius + 1), 10, 10, 20, DARKGRAY);
        DrawText("[R] to reset", 10, 30, 20, DARKGRAY);
        if(coloredSand) {
            DrawText("[C] to toggle colored sand (ON)", 10, 50, 20, ColorFromHSV(rainbowHue, 0.85f, 0.95f));
        } else {
            DrawText("[C] to toggle colored sand (OFF)", 10, 50, 20, DARKGRAY);
        }

        EndDrawing();
    }

    CloseWindow();

    return 0;
}