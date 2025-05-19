#include "Visualizer.hpp"

Visualizer::Visualizer(const std::vector<Grid> &data)
{
    unsigned n = data.size();
    unsigned k = 0;

    rows = data[0].get_lines();
    cols = data[0].get_columns();
    width = tile_size * cols;
    height = tile_size * rows;

    sf::Clock clock;

    window.create(sf::VideoMode(width, height), "Crystallization");

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        draw(data[k]);
        window.display();

        if (clock.getElapsedTime().asSeconds() > delay)
        {
            clock.restart();
            if (k < n - 1)
            {
                k++;
            }
        }
    }
}

void Visualizer::draw(const Grid &grid)
{
    std::vector<std::vector<sf::RectangleShape>> tiles(rows, std::vector<sf::RectangleShape>(cols));
    for (unsigned i = 0; i < rows; i++)
    {
        for (unsigned j = 0; j < cols; j++)
        {
            tiles[i][j].setSize(sf::Vector2f(tile_size, tile_size));
            tiles[i][j].setPosition(sf::Vector2f{(float)(j * tile_size), (float)(i * tile_size)});

            int state = grid.get_state(i, j);
            if (state == -1)
            {
                tiles[i][j].setFillColor(sf::Color::Green);
            }
            else
            {
                tiles[i][j].setFillColor(sf::Color(state)); //, state, state));
            }

            window.draw(tiles[i][j]);
        }
    }
}