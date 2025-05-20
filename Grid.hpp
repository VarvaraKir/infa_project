#include <iostream>
#include <cmath>
#include <algorithm>
#include <chrono>
#include <vector>
#include "Cell.hpp"
using namespace std;

class grid
{
    double dt;              // Шаг по времени
    double dx;              // Шаг по пространству
    int sum_column;         // Количество столбцов
    int sum_line;           // Количество строк
    double D;               // Коэффициент диффузии
    double ro;              // Плотность
    vector<vector<Cell>> a; // Двумерный вектор клеток (матрица)

public:
    // Конструктор и деструктор
    grid(int sum_column, int sum_line, double D, double dx, double dt, double ro);

    ~grid();

    // Методы для работы с концентрацией
    void grid_set_C(int column, int line, double C);
    double grid_get_C(int column, int line);

    // Физические процессы
    void diffusion(int column, int line);
    void crystallization(int column, int line);

    // Вспомогательные методы
    double square_summ(int i, int column, int line);
    // bool Grid_isSolution(int column, int line); // Проверка состояния клетки
};