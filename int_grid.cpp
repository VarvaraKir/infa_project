#include <iostream>
class grid
{
private:
    double dt;
    double dy;
    double dx;
    int sum_column;
    int sum_line;
    double D;
    double ro; //плотность
    int **a; //Должен быть не инт, а класс клетки int
public:
    grid(int sum_column, int sum_line, double D, double dx, double dt, double ro)
    {
        this->sum_column = sum_column;
        this->sum_line = sum_line;
        this->D = D;
        this->dx = dx;
        this->dt = dt;
        this->ro = ro;
        this->a = new int*[this->sum_column];
        for (int i = 0; i < this->sum_column; i++)
            this->a[i] = new int[this->sum_line];

    }
    ~grid()
    {
        for (int i = 0; i < this->sum_column; i++)
            delete[] this->a[i];
        delete[] this->a;
    }
    void print()
    {
        for(int i=0; i<this->sum_line; ++i)
        {
            for(int j=0; j<this->sum_column; ++j)
                std::cout<<this->a[j][i]<<" ";
            std::cout<<std::endl;
        }
    }
    void set_parametr(int parametr, int column, int line)//Написано для интов, в реальности сложнее
    {
        this->a[column][line] = parametr;
    }
    // void diffusion(int column, int line) //Диффузия
    // {
    //     double C = this->a[column][line].get_C(); //Функция должна получать значение концентрации в клетке
    //     double dC = this->a[column+1][line].get_C() + this->a[column-1][line].get_C() + this->a[column][line+1].get_C() + this->a[column][line-1].get_C(); 
    //     double C_new = C + this->D * this-> dt / this->dx / this->dx * (dC - 4*C);
    //     this->a[column][line].set_C(C_new); //Функция должна задавать значение концентрации в клетке 
    // }
    // double square_summ(int i, int column, int line)
    // {
    //     int n = 1 + 2*i;
    //     int num_column = 0, num_line=0;
    //     double summ = 0;
    //     for(int j=0; j<n; j++)
    //     {
    //         for(int k=0; k<n; k++)
    //         {
    //             if(this->a[column-i+num_column][line+i+num_line].solution()==true)//Проверяет, что это раствор
    //                 summ += this->a[column-i+num_column][line+i+num_line].get_C();
    //             ++num_line;
    //         }
    //         num_line = 0;
    //         ++num_column;
    //     }
    //     return summ;
    // }
    // void crystallization(int column, int line) //Перераспределение при кристаллизации
    // {
    //     double Cn = this->ro - this->a[column][line].get_C();
    //     bool flag = false;
    //     int i = 0;
    //     while(flag == false)
    //     {
    //         ++i;
    //         if (square_summ(i, column, line)>Cn)
    //             flag = true;
    //     }
    //     int num_column = 0, num_line=0;
    //     for(int j=0; j<2*i-1; j++)
    //     {
    //         for(int k=0; k<2*i-1; k++)
    //         {
    //             if (this->a[column-i+1+num_column][line+i-1+num_line].solution()==true)
    //                 this->a[column-i+1+num_column][line+i-1+num_line].set_C(0);
    //             ++num_line;
    //         }
    //         num_line = 0;
    //         ++num_column;
    //     }
    //     double factor = (Cn - square_summ(i-1, column, line))/(square_summ(i, column, line)-square_summ(i-1, column, line));
    //     for(int j=0; j<2*i+1; j++)
    //     {
    //         if (this->a[j][0].solution() == true)
    //         {
    //             double Ci = factor * this->a[j][0].get_C();
    //             this->a[j][0].set_C(Ci);
    //         }
    //     }
    //     for(int j=0; j<2*i+1; j++)
    //     {
    //         if (this->a[j][2*i+1].solution() == true)
    //         {
    //             double Ci = factor * this->a[j][2*i+1].get_C();
    //             this->a[j][2*i+1].set_C(Ci);
    //         }
    //     }
    //     for(int j=1; j<2*i; j++)
    //     {
    //         if (this->a[0][j].solution()==true)
    //         {
    //             double Ci = factor * this->a[0][j].get_C();
    //             this->a[0][j].set_C(Ci);
    //         }
    //         if(this->a[2*i+1][j].solution()==true)
    //         {
    //             double Ci = factor * this->a[2*i+1][j].get_C();
    //             this->a[2*i+1][j].set_C(Ci);
    //         }
    //     }
    // }

};
int main()
{
    grid ex(100, 200, 2.5, 0.01, 0.01, 12.3);
    ex.set_parametr(125, 0, 0);
    ex.print();
    return 0;
}