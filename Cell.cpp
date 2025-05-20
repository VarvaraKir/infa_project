#include "Cell.hpp"

// Конструктор
Cell::Cell()
{
    C = 0;
    crystallized = false;
    V0 = 0.65;
    C0 = 0.9;
    dt = 0.05;
    dx = 0.05;
    rho = 1.4;
    // cout << "Ha, Ha" << endl;
}

// Деструктор
Cell::~Cell() {}

// Задаем концентрацию
void Cell::setC(double C)
{
    this->C = C;
}
double Cell::get_rho()
{
    return rho;
}

// Возвращение концентрации
double Cell::getC() const
{
    return C;
}

// Получение вероятности растворения
double Cell::probability_of_dissolution(double dt, double dx)
{
    dissolution_rate();
    // std::cout<<W/V0<<std::endl;
    return 1 - exp(-W * dt / dx);
}

double Cell::probability_of_crystallization(double dt, double dx)
{
    dissolution_rate();
    return 1 - exp(-V * dt / dx);
}

// Получение скорости растворения
void Cell::dissolution_rate()
{
    double k = (C / C0) * (rho - C0) / (rho - C);
    V = V0 * k;
    W = V0 / k;
}

bool Cell::get_crystallized() const
{
    return crystallized;
}

void Cell::set_crystallized(bool is_crystallized)
{
    crystallized = is_crystallized;
    if (is_crystallized == true)
        C = rho;
}