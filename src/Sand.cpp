#include "Sand.hpp"

Color getSandColor(bool coloredSand, float& rainbowHue) {
    if(coloredSand) {
        rainbowHue += 80.0f * GetFrameTime();

        if(rainbowHue >= 360.0f) {
            rainbowHue -= 360.0f;
        }

        return ColorFromHSV(rainbowHue, 0.85f, 0.95f);
    }
    
    constexpr float hue = 42.0f;

    float saturation = static_cast<float>(GetRandomValue(55, 75) / 100.0f);
    float value = static_cast<float>(GetRandomValue(65, 90) / 100.0f);

    return ColorFromHSV(hue, saturation, value);
}

void paintSand(Grid& grid, int centerX, int centerY, int radius, Color color) {
    for(int dy = -radius; dy <= radius; dy++) {
        for(int dx = -radius; dx <= radius; dx++) {
            if(dx * dx + dy * dy > radius * radius) {
                continue;
            }

            int x = centerX + dx;
            int y = centerY + dy;

            if(grid.isInside(x, y)) {
                grid.setSand(x, y, color);
            }
        }
    }
}

