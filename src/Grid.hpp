// Grid.hpp

# pragma once

#include <vector>
#include <cstdint>
#include <raylib.h>

struct Cell {
    bool hasSand = false;
    Color color = YELLOW;
};

class Grid {
    public:
        Grid(int width, int height);

        int width() const;
        int height() const;

        bool hasSand(int x, int y) const;
        void setSand(int x, int y, Color color);
        void clearGrid();
        void swapCells(int x1, int y1, int x2, int y2);
        bool isInside(int x, int y) const;

        Color getColor(int x, int y) const;
    private:
        int m_width;
        int m_height;

        std::size_t index(int x, int y) const;

        std::vector<Cell> m_cells;
};