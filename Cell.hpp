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
    double probabilityOfDissolution( double dt, double dx);

    // Получение вероятности кристаллизации
    double probabilityOfcrystallization(double dt, double dx)

    // Получение скорости растворения
    void dissolutionRate();

    // // Проверка кристаллизованности
    // bool isNotCrystallized() const;

    // double random(double min, double max) const;
    bool get_solution();
    void set_crystal();
};
