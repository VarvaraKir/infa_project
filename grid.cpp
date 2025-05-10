#include "Cell.cpp"
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
    vector<vector<Cell>> a;; //Должен быть не инт, а класс клетки Cell
public:
    grid(int sum_column, int sum_line, double D, double dx, double dt, double ro)
    {
        this->sum_column = sum_column;
        this->sum_line = sum_line;
        this->D = D;
        this->dx = dx;
        this->dt = dt;
        this->ro = ro;
        this->a = vector<vector<Cell>>(sum_line, vector<Cell>(sum_column));
        for (int i = 0; i < this->sum_line; ++i)
        {
            for (int j = 0; j < this->sum_column; ++j)
            {
                this->a[i][j] = Cell();
            }
        }
        int size = this->a.size()
        for (int i = (size-1)/2; i < (size-1)/2+3; ++i)
        {
            for (int j = (size-1)/2; j < (size-1)/2; ++j)
            {
                this->a[i][j].set_crystal();
            }
        }

    }
    ~grid(){}
    grid& operator = (grid& b)
    {
        for (int i=0; i<this->sum_line; i++)
        {
            for (int j=0; j<this->sum_column; j++)
                this->a[i][j].setC(b.grid_get_C(i, j));
        }
        return *this;
    }
    // void print()
    // {
    //     for(int i=0; i<this->sum_line; ++i)
    //     {
    //         for(int j=0; j<this->sum_column; ++j)
    //             std::cout<<this->a[j][i]<<" ";
    //         std::cout<<std::endl;
    //     }
    // }
    // void set_parametr(int parametr, int column, int line)//Написано для интов, в реальности сложнее
    // {
    //     this->a[column][line] = parametr;
    // }
    double diffusion(int line, int column) //Диффузия
    {
        double C = this->a[line][column].getC(); //Функция должна получать значение концентрации в клетке
        double dC = this->a[line][column+1].getC() + this->a[line][column-1].getC() + this->a[line+1][column].getC() + this->a[line-1][column].getC(); 
        double C_new = C + this->D * this-> dt / this->dx / this->dx * (dC - 4*C);
        return C_new;
        // this->a[line][column].setC(C_new); //Функция должна задавать значение концентрации в клетке 
    }
    double square_summ(int i, int line, int column)
    {
        int n = 1 + 2*i;
        int num_column = 0, num_line=0;
        double summ = 0;
        for(int j=0; j<n; j++)
        {
            for(int k=0; k<n; k++)
            {
                if(this->a[line+i+num_line][column-i+num_column].get_solution()==true)//Проверяет, что это раствор
                    summ += this->a[line+i+num_line][column-i+num_column].getC();
                ++num_line;
            }
            num_line = 0;
            ++num_column;
        }
        return summ;
    }
    void crystallization(int line, int column) //Перераспределение при кристаллизации
    {
        double Cn = this->ro - this->a[line][column].getC();
        bool flag = false;
        int i = 0;
        while(flag == false)
        {
            ++i;
            if (square_summ(i, line, column)>Cn)
                flag = true;
        }
        int num_column = 0, num_line=0;
        for(int j=0; j<2*i-1; j++)
        {
            for(int k=0; k<2*i-1; k++)
            {
                if (this->a[line+i-1+num_line][column-i+1+num_column].get_solution()==true)
                    this->a[line+i-1+num_line][column-i+1+num_column].setC(0);
                ++num_line;
            }
            num_line = 0;
            ++num_column;
        }
        double factor = (Cn - square_summ(i-1, line, column))/(square_summ(i, line, column)-square_summ(i-1, line, column));
        for(int j=0; j<2*i+1; j++)
        {
            if (this->a[0][j].get_solution() == true)
            {
                double Ci = factor * this->a[0][j].getC();
                this->a[0][j].setC(Ci);
            }
        }
        for(int j=0; j<2*i+1; j++)
        {
            if (this->a[2*i+1][j].get_solution() == true)
            {
                double Ci = factor * this->a[2*i+1][j].getC();
                this->a[2*i+1][j].setC(Ci);
            }
        }
        for(int j=1; j<2*i; j++)
        {
            if (this->a[j][0].get_solution()==true)
            {
                double Ci = factor * this->a[j][0].getC();
                this->a[j][0].setC(Ci);
            }
            if(this->a[j][2*i+1].get_solution()==true)
            {
                double Ci = factor * this->a[j][2*i+1].getC();
                this->a[j][2*i+1].setC(Ci);
            }
        }
        this->a[line][column].set_crystal();
    }
    void grid_set_C(int line, int column, double C)
    {
        this->a[line][column].setC(C);
    }
    double grid_get_C(int line, int column)
    {
        return this->a[line][column].getC();
    }
    int get_lines()
    {
        return this->sum_line;
    }
    int get_columns()
    {
        return this->sum_column;
    }
    void random_crystallization(int line, int column)
    {
        int count = 0;
        double probability = this->a[line][column].probabilityOfcrystallization(this->dt, this->dx);
        for (int i=0; i<1000; i++)
        {
            if (random(0, 1)<0.5)
                count ++;
        }
        if (count < probability)
            crystallization(line, column);
    }
};