#pragma once

#include <string>
#include <vector>
#include <SFML/Graphics.hpp>

#include "Grid.hpp"

class Visualizer
{
private:
    sf::RenderWindow window;

    double delay = 0.1;
    unsigned tile_size = 8;
    unsigned rows, cols;
    unsigned width, height;

public:
    Visualizer(const std::vector<Grid> &data);

    void draw(const Grid &grid);
};