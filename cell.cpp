#include <iostream>
#include <random>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <algorithm>
#include "cell.hpp"
using namespace std;
class cell
{
protected:
    // Вводим сами
    double C, Cv, C0, V0, D, p; // концентрация, концентрация вещества в растворе,
                                // равновесная концентрация, скорость роста кристалла, Коэфф диффузии,
                                // плотность твердого вещества (для кристаллизации)
    // Считаем в процессе
    double V, W, P, Q; // средняя скорость роста, средняя скорость растворения грани кристалла,
                       // вероятность кристализации, вероятность растворения

public:
    // Конструктор
    cell(double c, double d)
    {
        this->C = c;
        this->D = d;
    }

    // Деструктор
    ~cell() {}

    // Задаем концентрацию
    void set_C(double c)
    {
        this->C = c;
    }

    // Возвращение концентрации
    double get_C() const
    {
        return this->C;
    }

    // Получение вероятности растворения
    double Prob_Dissolut(double W, double dt, double dx)
    {
        this->Q = 1 - exp(W * dt / dx);
        return Q;
    }

    // Получение скорости роста
    double SpeedRise() const
    {
        return this->V0 * (this->Cv / this->C0) * (this->p - this->C0) / (this->p - this->Cv);
    }

    // Получение скорости растворения
    double SpeedDissolve() const
    {
        return this->V0 * (this->C0 / this->Cv) * (this->p - this->Cv) / (this->p - this->C0);
    }
};

class CrystalSystem : public cell
{
public:
    // Инициализация генератора случайных чисел
    CrystalSystem()
    {
        srand(time(0)); // для rand()
    }

    // Расчет вероятности кристаллизации
    double Prob_Crystal(double V, double dt, double dx)
    {
        P = 1.0 - exp(-V * dt / dx); // не знаю нужен - в формуле или нет
        P = clamp(P, 0.01, 0.99);    // Ограничиваем вероятность диапазоном [0.01, 0.99]
        return P;
    }

    // Проверка состояния вещества
    bool IsSolution()
    {
        double random_value = (double)rand() / RAND_MAX;
        return (random_value >= P); // true = раствор (не кристаллизовался), false = кристаллизация
    }
};
