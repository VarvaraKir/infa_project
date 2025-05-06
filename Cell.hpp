#include <iostream>
#include <random>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <chrono>

class Cell
{

    // Вводим сами
    double C, Cv, C0, V0, D, rho, dt, dx; // концентрация, концентрация вещества в растворе,
                                          // равновесная концентрация, скорость роста кристалла, Коэфф диффузии,
                                          // плотность твердого вещества (для кристаллизации), шаг по времени и по расстоянию
    // Считаем в процессе
    double V, W, P, Q; // средняя скорость роста, средняя скорость растворения грани кристалла,
                       // вероятность кристализации, вероятность растворения

public:
    // Конструктор
    Cell(double c, double d);
    // Деструктор
    ~Cell();

    // Задаем концентрацию
    void setC(double c);

    // Возвращение концентрации
    double getC() const;

    // Получение вероятности растворения
    double probabilityOfDissolution(double W, double dt, double dx);

    // Получение скорости роста
    void growthRate();

    // Получение скорости растворения
    void dissolutionRate();

    // Проверка кристаллизованности
    bool isNotCrystallized() const;

    double randomMy(double min, double max) const;
};

// class CrystalSystem : public Cell
// {
// public:
//     // Инициализация генератора случайных чисел
//     CrystalSystem()
//     {
//     }

//     // Расчет вероятности кристаллизации
//     double Prob_Crystal(double V, double dt, double dx)
//     {
//     }

//     // Проверка состояния вещества
//     bool IsSolution()
//     {
//     }
// };
