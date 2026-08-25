// Grid.cpp

#include "Grid.hpp"

#include <algorithm>

Grid::Grid(int width, int height):
    m_width(width),
    m_height(height),
    m_cells(width * height)
{
}

int Grid::width() const {
    return m_width;
}

int Grid::height() const {
    return m_height;
}

std::size_t Grid::index(int x, int y) const {
    return y * m_width + x;
}

bool Grid::hasSand(int x, int y) const {
    return m_cells[index(x,y)].hasSand;
}

void Grid::setSand(int x, int y, Color color) {
    Cell& cell = m_cells[index(x, y)];

    cell.hasSand = true;
    cell.color = color;
}

Color Grid::getColor(int x, int y) const {
    return m_cells[index(x, y)].color;
}

void Grid::clearGrid(){
    std::fill(m_cells.begin(), m_cells.end(), Cell{});
}

bool Grid::isInside(int x, int y) const {
    return  x >= 0 && x < m_width && 
            y >= 0 && y < m_height;
}


void Grid::swapCells(int x1, int y1, int x2, int y2) {
    std::swap(
        m_cells[index(x1, y1)],
        m_cells[index(x2, y2)]
    );
}
