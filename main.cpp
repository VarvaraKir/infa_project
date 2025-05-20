#include "Grid.hpp"
#include "Visualizer.hpp"

#include <iostream>
#include <vector>
int main()
{
    int lines = 100;
    int columns = 100;

    int t = 80;
    double D = 0.01;
    double dt = 0.05;
    double dx = dt;
    double rho = 1.4;
    std::vector<Grid> data_t;
    Grid data(lines, columns, D, dx, dt);
    Grid data1(lines, columns, D, dx, dt);
    data_t.push_back(data);
    double C;
    for (int k =0; k<t; k++)
    {
        for (int i=1; i<data.get_lines()-1; i++)
        {
            for(int j=1; j<data.get_columns()-1; j++)
            {
                C = data.diffusion(i, j);
                data1.grid_set_C(i, j , C);
            }
        }
        data = data1;
        data.crystallize();
        data_t.push_back(data);
    }
    Visualizer visualizer(data_t);
    return 0;
}