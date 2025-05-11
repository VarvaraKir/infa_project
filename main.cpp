#include "grid.cpp"
int main()
{
    grid data(99, 99, 0.01, 0.05, 0.05, 1.4);
    grid data1(99, 99, 0.01, 0.05, 0.05, 1.4);
    int t;
    double C;
    cin>>t;
    // data.print();
    for (int k =0; k<t; k++)
    {
        for (int i=1; i<data.get_lines()-1; i++)
        {
            for(int j=1; j<data.get_columns()-1; j++)
            {
                C = data.diffusion(i, j);
                data1.grid_set_C(i, j , C);
            }
        }
        data = data1;
        for (int i=1; i<data.get_lines()-1; i++)
        {
            for(int j=1; j<data.get_columns()-1; j++)
            {
                data.random_crystallization(i, j);
            }
        }
    }
    data.print();
    return 0;
}