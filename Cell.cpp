#include <iostream>
#include <random>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <chrono>
using namespace std;

class Cell
{

    // Вводим сами
    double C, Cv, C0, V0, D, rho, dt, dx; // концентрация, концентрация вещества в растворе,
                                          // равновесная концентрация, скорость роста кристалла, Коэфф диффузии,
                                          // плотность твердого вещества (для кристаллизации), шаг по времени и по расстоянию
    // Считаем в процессе
    double V, W, P, Q; // средняя скорость роста, средняя скорость растворения грани кристалла,
                       // вероятность кристализации, вероятность растворения
    bool solution;

public:
    // Конструктор
    Cell(double c, double d);

    // конструктор2
    Cell();

    // Деструктор
    ~Cell();

    // Задаем концентрацию
    void setC(double c);

    // Возвращение концентрации
    double getC() const;

    // Получение вероятности растворения
    double probabilityOfDissolution(double dt, double dx);

    // Получение вероятности кристаллизации
    double probabilityOfcrystallization(double dt, double dx);

    // Получение скорости растворения
    void dissolutionRate();

    // // Проверка кристаллизованности
    // bool isNotCrystallized() const;

    // double random(double min, double max) const;
    bool get_solution();
    void set_crystal();
};

// Конструктор
Cell::Cell(double c, double d)
{
    this->C = c;
    this->D = d;
}

// Конструктор 2
Cell::Cell()
{
    this->C = 0;
    this->solution = true;
    // cout << "Ha, Ha" << endl;
}

// Деструктор
Cell::~Cell() {}

// Задаем концентрацию
void Cell::setC(double c)
{
    this->C = c;
}

// Возвращение концентрации
double Cell::getC() const
{
    return this->C;
}

// Получение вероятности растворения
double Cell::probabilityOfDissolution(double dt, double dx)
{
    dissolutionRate();
    this->Q = 1 - exp(-1*this->W * dt / dx);
    return Q;
}
double Cell::probabilityOfcrystallization(double dt, double dx)
{
    dissolutionRate();
    this->Q = 1 - exp(-1*this->V * dt / dx);
    return Q;
}
// Получение скорости растворения
void Cell::dissolutionRate()
{
    this->W = this->V0 * (this->C0 / this->Cv) * (this->rho - this->Cv) / (this->rho - this->C0);
    this->V = this->V0 *(this->Cv / this->C0) * (this->rho - this->C0) / (this->rho - this->Cv);
}

// bool Cell::isNotCrystallized() const
// {
//     double V = this->V0 * (this->Cv / this->C0) * (this->rho - this->C0) / (this->rho - this->Cv);
//     double p = 1 - exp(-V * dt / dx);

//     return random(0, 1) < p; // true = раствор (не кристаллизовался), false = кристаллизация
// }
bool Cell::get_solution()
{
    return this->solution;
}
void Cell::set_crystal()
{
    this->solution = false;
}
double random(double min, double max)
{
    unsigned seed = std::chrono::steady_clock::now().time_since_epoch().count();
    static std::default_random_engine e(seed);
    std::uniform_real_distribution<double> d(min, max);
    return d(e);
}
