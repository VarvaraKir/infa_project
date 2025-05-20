#include "Grid.hpp"

grid::grid(int sum_column, int sum_line, double D, double dx, double dt, double ro)
{
    this->sum_column = sum_column;
    this->sum_line = sum_line;
    this->D = D;
    this->dx = dx;
    this->dt = dt;
    this->ro = ro;
    this->a = vector<vector<Cell>>(sum_line, vector<Cell>(sum_column));
    for (int i = 0; i < this->sum_line; ++i)
    {
        for (int j = 0; j < this->sum_column; ++j)
        {
            this->a[i][j] = Cell();
        }
    }
}
grid::~grid() {}
// void print()
// {
//     for(int i=0; i<this->sum_line; ++i)
//     {
//         for(int j=0; j<this->sum_column; ++j)
//             std::cout<<this->a[j][i]<<" ";
//         std::cout<<std::endl;
//     }
// }
// void set_parametr(int parametr, int column, int line)//Написано для интов, в реальности сложнее
// {
//     this->a[column][line] = parametr;
// }
void grid::diffusion(int column, int line) // Диффузия
{
    double C = this->a[column][line].getC(); // Функция должна получать значение концентрации в клетке
    double dC = this->a[column + 1][line].getC() + this->a[column - 1][line].getC() + this->a[column][line + 1].getC() + this->a[column][line - 1].getC();
    double C_new = C + this->D * this->dt / this->dx / this->dx * (dC - 4 * C);
    this->a[column][line].setC(C_new); // Функция должна задавать значение концентрации в клетке
}
double grid::square_summ(int i, int column, int line)
{
    int n = 1 + 2 * i;
    int num_column = 0, num_line = 0;
    double summ = 0;
    for (int j = 0; j < n; j++)
    {
        for (int k = 0; k < n; k++)
        {
            if (this->a[column - i + num_column][line + i + num_line].isNotCrystallized() == true) // Проверяет, что это раствор
                summ += this->a[column - i + num_column][line + i + num_line].getC();
            ++num_line;
        }
        num_line = 0;
        ++num_column;
    }
    return summ;
}
void grid::crystallization(int column, int line) // Перераспределение при кристаллизации
{
    double Cn = this->ro - this->a[column][line].getC();
    bool flag = false;
    int i = 0;
    while (flag == false)
    {
        ++i;
        if (square_summ(i, column, line) > Cn)
            flag = true;
    }
    int num_column = 0, num_line = 0;
    for (int j = 0; j < 2 * i - 1; j++)
    {
        for (int k = 0; k < 2 * i - 1; k++)
        {
            if (this->a[column - i + 1 + num_column][line + i - 1 + num_line].isNotCrystallized() == true)
                this->a[column - i + 1 + num_column][line + i - 1 + num_line].setC(0);
            ++num_line;
        }
        num_line = 0;
        ++num_column;
    }
    double factor = (Cn - square_summ(i - 1, column, line)) / (square_summ(i, column, line) - square_summ(i - 1, column, line));
    for (int j = 0; j < 2 * i + 1; j++)
    {
        if (this->a[j][0].isNotCrystallized() == true)
        {
            double Ci = factor * this->a[j][0].getC();
            this->a[j][0].setC(Ci);
        }
    }
    for (int j = 0; j < 2 * i + 1; j++)
    {
        if (this->a[j][2 * i + 1].isNotCrystallized() == true)
        {
            double Ci = factor * this->a[j][2 * i + 1].getC();
            this->a[j][2 * i + 1].setC(Ci);
        }
    }
    for (int j = 1; j < 2 * i; j++)
    {
        if (this->a[0][j].isNotCrystallized() == true)
        {
            double Ci = factor * this->a[0][j].getC();
            this->a[0][j].setC(Ci);
        }
        if (this->a[2 * i + 1][j].isNotCrystallized() == true)
        {
            double Ci = factor * this->a[2 * i + 1][j].getC();
            this->a[2 * i + 1][j].setC(Ci);
        }
    }
}
void grid::grid_set_C(int column, int line, double C)
{
    this->a[column][line].setC(C);
}
double grid::grid_get_C(int column, int line)
{
    return this->a[column][line].getC();
}