#include "Cell.hpp"
using namespace std;

// Конструктор
Cell::Cell(double c, double d)
{
    this->C = c;
    this->D = d;
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

double random(double min, double max)
{
    unsigned seed = std::chrono::steady_clock::now().time_since_epoch().count();
    static std::default_random_engine e(seed);
    std::uniform_real_distribution<double> d(min, max);
    return d(e);
}

// class CrystalSystem : public Cell
// {
// public:
//     // Инициализация генератора случайных чисел
//     CrystalSystem()
//     {
//         srand(time(0)); // для rand()
//     }

//     // Расчет вероятности кристаллизации
//     double Prob_Crystal(double V, double dt, double dx)
//     {
//         P = 1.0 - exp(-V * dt / dx); // не знаю нужен - в формуле или нет
//         P = clamp(P, 0.01, 0.99);    // Ограничиваем вероятность диапазоном [0.01, 0.99]
//         return P;
//     }

//     // Проверка состояния вещества
//     bool IsSolution()
//     {
//         double random_value = (double)rand() / RAND_MAX;
//         return (random_value >= P); // true = раствор (не кристаллизовался), false = кристаллизация
//     }
// };
