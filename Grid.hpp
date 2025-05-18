#pragma once

#include <vector>
#include <algorithm>

#include "Cell.hpp"

class Grid
{
private:
    double dt;
    double dy;
    double dx;
    unsigned sum_column;
    unsigned sum_line;
    double D;
    double rho; // плотность
    std::vector<std::vector<Cell>> a;

public:
    Grid(int sum_column, int sum_line, double D, double dx, double dt, double rho);

    ~Grid();

    void diffuse();

    double diffusion(int line, int column); // Диффузия

    void dissolve();

    void crystallize();

    bool has_crystal_neighbour(unsigned i, unsigned j) const;

    void crystallization(int line, int column); // Перераспределение при кристаллизации

    double square_summ(int i, unsigned line, unsigned column) const;

    double grid_get_C(unsigned line, unsigned column) const;

    void grid_set_C(unsigned line, unsigned column, double C);

    bool grid_get_crystallized(unsigned line, unsigned column) const;

    void grid_set_crystallized(unsigned line, unsigned column, bool is_crystallized);

    int get_lines() const;

    int get_columns() const;

    int get_state(int line, int column) const;

    double random_double(double min, double max);
};
