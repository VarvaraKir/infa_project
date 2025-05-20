#pragma once

#include <iostream>
#include <random>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <chrono>

class Cell
{
private:
    // Вводим сами
    double C, C0, V0, D, rho, dt, dx; // концентрация, концентрация вещества в растворе,
                                      // равновесная концентрация, скорость роста кристалла, Коэфф диффузии,
                                      // плотность твердого вещества (для кристаллизации), шаг по времени и по расстоянию
    // Считаем в процессе
    double V, W; // средняя скорость роста, средняя скорость растворения грани кристалла,

    bool crystallized;

public:
    // Конструктор
    Cell();

    // Деструктор
    ~Cell();

    // Задаем концентрацию
    void setC(double C);

    // Возвращение концентрации
    double getC() const;

    // Получение вероятности растворения
    double probability_of_dissolution(double dt, double dx);

    // Получение вероятности кристаллизации
    double probability_of_crystallization(double dt, double dx);

    // Получение скорости растворения
    void dissolution_rate();

    bool get_crystallized() const;

    void set_crystallized(bool is_crystal);
    double get_rho();
};
