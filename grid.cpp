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
        int size = this->sum_line;
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
        this->a[(size-1)/2][(size-1)/2].set_crystal();
        this->a[(size-1)/2][(size-1)/2].setC(this->ro);
        for (int k = 1; k < 10; ++k)
        {
            for (int i = (size-1)/2-k; i < (size-1)/2+k+1; ++i)
            {
                for (int j = (size-1)/2-k; j < (size-1)/2+k+1; ++j)
                {
                    if (this->a[i][j].get_solution() == true) this->a[i][j].setC(this->ro*(102-5*k)/100);
                    // cout<<i<<' '<<j<<' '<<a[i][j].getC()<<endl;
                }
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
        double summ = 0;
        for(int j=0; j<n; j++)
        {
            for(int k=0; k<n; k++)
            {
                if(this->a[line-i+j][column-i+k].get_solution()==true)//Проверяет, что это раствор
                    summ += this->a[line-i+j][column-i+k].getC();
            }
        }
        return summ;
    }
    void crystallization(int line, int column) //Перераспределение при кристаллизации
    {
        double Cn = this->ro - this->a[line][column].getC();
        this->a[line][column].set_crystal();
        this->a[line][column].setC(this->ro);
        bool flag = false;
        int i = 0;
        while(flag == false)
        {
            ++i;
            if (square_summ(i, line, column)>Cn)
                flag = true;
        }
        double factor = (Cn - square_summ(i-1, line, column))/(square_summ(i, line, column)-square_summ(i-1, line, column));
        for(int j=0; j<2*i-1; j++)
        {
            for(int k=0; k<2*i-1; k++)
            {
                if (this->a[line-i+1+j][column-i+1+k].get_solution()==true)
                    this->a[line-i+1+j][column-i+1+k].setC(0);
            }
        }
        for(int j=0-i; j<i+1; j++)
        {
            if (this->a[line-i][column + j].get_solution() == true)
            {
                double Ci = factor * this->a[line - i][column + j].getC();
                this->a[line - i][column + j].setC(Ci);
            }
        }
        for(int j=0-i; j<i+1; j++)
        {
            if (this->a[line + i][column + j].get_solution() == true)
            {
                double Ci = factor * this->a[line + i][column + j].getC();
                this->a[line + i][column + j].setC(Ci);
            }
        }
        for(int j=line - i + 1; j<line + i; j++)
        {
            if (this->a[j][column - i].get_solution()==true)
            {
                double Ci = factor * this->a[j][column - i].getC();
                this->a[j][column - i].setC(Ci);
            }
            if(this->a[j][column + i].get_solution()==true)
            {
                double Ci = factor * this->a[j][column + i].getC();
                this->a[j][column + i].setC(Ci);
            }
        }
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
        // if (probability!= 0 ) cout<<probability<<endl;
        for (int i=0; i<1000; i++)
        {
            if (random(0, 1)<0.5)
                count ++;
        }
        if (count < probability*1000)
        {
            crystallization(line, column);
            // print();
        }
    }
    void print()
    {
        for (int i=0; i<sum_line; i++)
        {
            for (int j=0; j<sum_column; j++)
            {
                if (this->a[i][j].get_solution() == false) cout<<'1';
                else
                {
                    if (this->a[i][j].getC() == 0) cout<<' ';
                    else cout<<'*';
                }
                cout<<' ';
            }
            cout<<endl;
        }
    }
};