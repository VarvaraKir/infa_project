#include <iostream>
#include <random>
#include <math.h>
#include <cmath>
class cell
{
protected:
    // Вводим сами
    double C, Cv, C0, V0, D, V, W, P, Q, p; // концентрация, концентрация вещества в растворе,
                                            // равновесная концентрация, скорость роста кристалла, Коэфф диффузии,
                                            // плотность твердого вещества (для кристаллизации)
    // Считаем в процессе
    double V1, W1, P1, Q1;  // средняя скорость роста, средняя скорость растворения грани кристалла,
                        // вероятность кристализации, вероятность растворения, плотность (твердого ) ???? вещества
    bool crystal_event; // для кристаллизации
public:
    // Конструктор вектора размерности n
    cell(double c, double d)
    {
        this->C = c;
        this->D = d;
    }
    cell(){}

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

    // Получение вероятности кристаллизации
    double Prob_Crystal(double V, double dt, double dx)
    {
        this->P = 1 - exp(V * dt / dx);
        // для проверки
        if (P < 0.01)
        {
            P = 0.01;
        }
        else
        {
            if (P > 0.99)
                P = 0.99;
            return P;
        }
    }

    // Проверяет крисстализацию 
    bool solution()
    {
        if (this->crystal_event == 1)
        {
            return false;
        }
        else
            return true;
    }

    // Получение вероятности кристаллизации
    double Prob_Dissolut(double W, double dt, double dx) // как написать дельта т и дельта икс
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

    // // Генерация случайной вероятности
    // double RandProbabi() const
    // {
    //     std::random_device P_rand;                       // создаем переменную
    //     std::mt19937 gen(P_rand());                      // инициализирует генератор псевдослучайных чисел с использованием переменной
    //     std::uniform_int_distribution<> distr(0.2, ???); // определяет распределение, в котором будут генерироваться
    //     // целые числа в диапазоне.
    // }
};