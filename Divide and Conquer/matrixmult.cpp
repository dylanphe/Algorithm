#include <iostream>
#include <vector>


using namespace std;

void printMatrix(vector<vector <int>> matrix, int m, int n)
{
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

void matrixMult(vector<vector <int>> A, vector <vector <int>> B, int m, int n, int p)
{
    vector<vector <int>> prod(m, vector<int> (p, 0));
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < p; j++)
        {
            for (int k = 0; k < n; k++)
            {
                prod[i][j] += (A[i][k] * B[k][j]);
            }
        }
    }
    cout << "Result = " << endl;
    printMatrix(prod, m, p);
}

int main()
{
    int m = 4;
    int n = 4;
    int p = 4;
    vector<vector<int>> A = {   {1, 1, 1, 1},
                                {2, 2, 2, 2},
                                {3, 3, 3, 3},
                                {2, 2, 2, 2}  };
    vector<vector<int>> B = {   {1, 1, 1, 1},
                                {2, 2, 2, 2},
                                {3, 3, 3, 3}, 
                                {2, 2, 2, 2}  };

    cout << "Matrix A = " << endl;
    //Print A
    printMatrix(A, m, n);
    cout << "Matrix B = " << endl;
    //Print B
    printMatrix(A, m, n);

    matrixMult(A,B,m,n,p);

    return 0;
}