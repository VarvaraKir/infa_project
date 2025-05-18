#include "Grid.hpp"
Grid::Grid(int sum_column, int sum_line, double D, double dx, double dt, double rho)
{
    this->sum_column = sum_column;
    this->sum_line = sum_line;
    this->D = D;
    this->dx = dx;
    this->dt = dt;
    this->rho = rho;

    a = std::vector<std::vector<Cell>>(sum_line, std::vector<Cell>(sum_column));
    for (int i = 0; i < this->sum_line; ++i)
    {
        for (int j = 0; j < this->sum_column; ++j)
        {
            a[i][j] = Cell();
        }
    }

    // Наливаем раствор в центральную область
    unsigned center = sum_line / 2;
    unsigned k = 30;
    for (unsigned i = center - k; i < center + k + 1; i++)
    {
        for (unsigned j = center - k; j < center + k + 1; j++)
        {
            a[i][j].setC(rho);
        }
    }
    // Кристаллизируем центр
    a[center][center].set_crystallized(true);
}

Grid::~Grid() {}

void Grid::diffuse()
{
}

double Grid::diffusion(int line, int column) // Диффузия
{
    if (a[line][column].get_crystallized())
    {
        return rho;
    }

    double C = a[line][column].getC();
    double dC = a[line][column + 1].getC() * !a[line][column + 1].get_crystallized() +
                a[line][column - 1].getC() * !a[line][column - 1].get_crystallized() +
                a[line + 1][column].getC() * !a[line + 1][column].get_crystallized() +
                a[line - 1][column].getC() * !a[line - 1][column].get_crystallized();

    return C + D * dt / (dx * dx) * (dC - 4 * C);
}

void Grid::dissolve()
{
    for (unsigned i = 0; i < sum_line; i++)
    {
        for (unsigned j = 0; j < sum_column; j++)
        {
            if (a[i][j].get_crystallized() && i != sum_line / 2 && j != sum_line / 2) // Центральная точка всегда остается кристаллизированной
            {
                double probability = a[i][j].probability_of_dissolution(dt, dx);
                if (random_double(0, 1) < probability)
                {
                    a[i][j].set_crystallized(false);
                }
            }
        }
    }
}

void Grid::crystallize()
{
    std::vector<std::pair<unsigned, unsigned>> candidates;
    for (unsigned i = 1; i < sum_line - 1; i++)
    {
        for (unsigned j = 1; j < sum_column - 1; j++)
        {
            if (has_crystal_neighbour(i, j))
            {
                candidates.push_back({i, j});
            }
        }
    }

    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(candidates.begin(), candidates.end(), g);

    for (int k = 0; k < candidates.size(); k++)
    {
        unsigned i = candidates[k].first;
        unsigned j = candidates[k].second;

        double probability = a[i][j].probability_of_crystallization(dt, dx);
        if (random_double(0, 1) < probability)
        {
            crystallization(i, j);
        }
    }
}

bool Grid::has_crystal_neighbour(unsigned i, unsigned j) const
{
    return a[i][j + 1].get_crystallized() || a[i + 1][j].get_crystallized() ||
           a[i][j - 1].get_crystallized() || a[i - 1][j].get_crystallized() ||
           a[i + 1][j + 1].get_crystallized() || a[i + 1][j - 1].get_crystallized() ||
           a[i - 1][j + 1].get_crystallized() || a[i - 1][j - 1].get_crystallized();
}

void Grid::crystallization(int line, int column) // Перераспределение при кристаллизации
{
    double Cn = rho - a[line][column].getC();
    a[line][column].set_crystallized(true);
    a[line][column].setC(rho);

    int r = 0;
    while (square_summ(r, line, column) < Cn)
    {
        r++;
    }
    double factor = (Cn - square_summ(r - 1, line, column)) / (square_summ(r, line, column) - square_summ(r - 1, line, column));
    for (int i = 0; i < 2 * r - 1; i++)
    {
        for (int j = 0; j < 2 * r - 1; j++)
        {
            if (!a[line - r + 1 + i][column - r + 1 + j].get_crystallized())
            {
                a[line - r + 1 + i][column - r + 1 + j].setC(0);
            }
        }
    }

    for (int j = -r; j < r + 1; j++)
    {
        if (!a[line - r][column + j].get_crystallized())
        {
            double Cr = factor * a[line - r][column + j].getC();
            a[line - r][column + j].setC(Cr);
        }
        if (!a[line + r][column + j].get_crystallized())
        {
            double Cr = factor * a[line + r][column + j].getC();
            a[line + r][column + j].setC(Cr);
        }
    }

    for (int j = -r; j < r + 1; j++)
    {
        if (!a[line + j][column - r].get_crystallized())
        {
            double Cr = factor * a[line + j][column - r].getC();
            a[line + j][column - r].setC(Cr);
        }
        if (!a[line + j][column + r].get_crystallized())
        {
            double Cr = factor * a[line + j][column + r].getC();
            a[line + j][column + r].setC(Cr);
        }
    }
}

double Grid::square_summ(int r, unsigned line, unsigned column) const
{
    int n = 1 + 2 * r;
    double summ = 0;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (!a[line - r + i][column - r + j].get_crystallized()) // Проверяет, что это раствор
            {
                summ += a[line - r + i][column - r + j].getC();
            }
        }
    }

    return summ;
}

double Grid::grid_get_C(unsigned line, unsigned column) const
{
    return a[line][column].getC();
}

void Grid::grid_set_C(unsigned line, unsigned column, double C)
{
    a[line][column].setC(C);
}

bool Grid::grid_get_crystallized(unsigned line, unsigned column) const
{
    return a[line][column].get_crystallized();
}

void Grid::grid_set_crystallized(unsigned line, unsigned column, bool is_crystallized)
{
    a[line][column].set_crystallized(is_crystallized);
}

int Grid::get_lines() const
{
    return sum_line;
}

int Grid::get_columns() const
{
    return sum_column;
}

int Grid::get_state(int line, int column) const
{
    if (a[line][column].get_crystallized())
    {
        return -1;
    }
    else
    {
        return a[line][column].getC() / rho * 255;
    }
}

double Grid::random_double(double min, double max)
{
    unsigned seed = std::chrono::steady_clock::now().time_since_epoch().count();
    static std::default_random_engine e(seed);
    std::uniform_real_distribution<double> d(0, 1);
    return d(e);
}