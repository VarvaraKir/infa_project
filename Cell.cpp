#include "Cell.hpp"

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
double Cell::probabilityOfDissolution(double W, double dt, double dx)
{
    this->Q = 1 - exp(-W * dt / dx);
    return Q;
}

// Получение скорости растворения
void Cell::dissolutionRate()
{
    this->W = this->V0 * (this->C0 / this->Cv) * (this->rho - this->Cv) / (this->rho - this->C0);
}

bool Cell::isNotCrystallized() const
{
    double V = this->V0 * (this->Cv / this->C0) * (this->rho - this->C0) / (this->rho - this->Cv);
    double p = 1 - exp(-V * dt / dx);

    return random(0, 1) < p; // true = раствор (не кристаллизовался), false = кристаллизация
}

double Cell::random(double min, double max) const
{
    unsigned seed = std::chrono::steady_clock::now().time_since_epoch().count();
    static std::default_random_engine e(seed);
    std::uniform_real_distribution<double> d(min, max);
    return d(e);
}
