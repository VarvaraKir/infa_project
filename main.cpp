#include "grid.cpp"
int main()
{
    grid ex(5, 4, 2.5, 0.01, 0.01, 12.3);
    ex.grid_set_C(0, 0, 1.5);
    auto a = ex.grid_get_C(0, 0);
    std::cout<<a;
    return 0;
}