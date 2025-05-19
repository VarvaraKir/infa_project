#include "Grid.hpp"
#include "Visualizer.hpp"

#include <iostream>
#include <vector>

int main()
{
    int lines = 100;
    int columns = 100;

    int t = 60;
    std::vector<Grid> data;
    data.push_back(Grid(lines, columns, 0.01, 0.05, 0.05, 1.4));

    for (unsigned k = 1; k <= t; k++)
    {
        data.push_back(Grid(lines, columns, 0.01, 0.05, 0.05, 1.4));

        for (unsigned i = 1; i < lines - 1; i++)
        {
            for (unsigned j = 1; j < columns - 1; j++)
            {
                data[k].grid_set_crystallized(i, j, data[k - 1].grid_get_crystallized(i, j));
                data[k].grid_set_C(i, j, data[k - 1].diffusion(i, j));
            }
        }

        data[k].dissolve();
        data[k].crystallize();
    }

    Visualizer visualizer(data);

    return 0;
}