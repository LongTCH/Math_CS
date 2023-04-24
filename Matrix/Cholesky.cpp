#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;

const int maxN = 100;

double DetOfMatrix(double mat[maxN][maxN], int n)
{
    double det = 0;
    double submat[maxN][maxN];

    if (n == 1)
    { // base case for 1x1 matrix
        return mat[0][0];
    }
    else if (n == 2)
    { // base case for 2x2 matrixT
        return ((mat[0][0] * mat[1][1]) - (mat[1][0] * mat[0][1]));
    }
    else
    {
        for (int x = 0; x < n; x++)
        {
            int subi = 0;
            for (int i = 1; i < n; i++)
            {
                int subj = 0;
                for (int j = 0; j < n; j++)
                {
                    if (j == x)
                        continue;
                    submat[subi][subj] = mat[i][j];
                    subj++;
                }
                subi++;
            }
            det = det + (pow(-1, x) * mat[0][x] * DetOfMatrix(submat, n - 1));
        }
    }
    return det;
}

bool IsSymmetry(double mat[maxN][maxN], int n)
{
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
            if (mat[i][j] != mat[j][i])
                return false;
    return true;
}

bool PositiveDefinite(double mat[maxN][maxN], int n)
{
    for (int i = 0; i < n; i++)
        if (mat[i][i] <= 0 || !DetOfMatrix(mat, i + 1))
            return false;
    return true;
}

void printMatrix(double mat[maxN][maxN], int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            cout << setw(10) << mat[i][j] << "\t";
        cout << endl;
    }
    cout << endl;
}

void printT_Matrix(double mat[maxN][maxN], int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
            cout << setw(10) << mat[j][i] << "\t";
        cout << endl;
    }
}

void classical_Cholesky(double mat[maxN][maxN], int n)
{
    double low[maxN][maxN];
    for (int i = 0; i < maxN; i++)
    {
        for (int j = 0; j < maxN; j++)
            low[i][j] = 0;
    }
    for (int i = 0; i < n; i++)
        for (int j = 0; j <= i; j++)
        {
            double sum = 0;
            for (int k = 0; k < j; k++)
            {
                sum += low[i][k] * low[j][k];
            }
            if (i == j)
            {
                low[i][i] = sqrt(max(mat[i][i] - sum, 0.0));
            }
            else
            {
                low[i][j] = 1.0 / low[j][j] * (mat[i][j] - sum);
            }
        }
    cout << "Matrix A =" << endl;
    printMatrix(mat, n);
    cout << "Phan ra Cholesky A = L * LT:" << endl;
    cout << "Matrix L =" << endl;
    printMatrix(low, n);
    cout << "Matrix LT =" << endl;
    printT_Matrix(low, n);
}

void Cholesky(double mat[maxN][maxN], int n)
{
    double l[maxN][maxN], d[maxN][maxN];
    for (int i = 0; i < maxN; i++)
    {
        for (int j = 0; j < maxN; j++)
        {
            l[i][j] = d[i][j] = 0;
        }
    }
    for (int i = 0; i < n; i++)
    {
        d[i][i] = mat[i][i];
        l[i][i] = 1;
        for (int k = 0; k < i; k++)
            d[i][i] -= l[i][k] * l[i][k] * d[k][k];
        for (int j = i + 1; j < n; j++)
        {
            l[j][i] = mat[j][i];
            for (int k = 0; k < i; k++)
                l[j][i] -= l[j][k] * l[i][k] * d[k][k];
            l[j][i] /= d[i][i];
        }
    }
    cout << "Matrix A =" << endl;
    printMatrix(mat, n);
    cout << "Phan ra Cholesky A = L * D * LT:" << endl; 
    cout << "Matrix L =" << endl;
    printMatrix(l, n);
    cout << "Matrix D =" << endl;
    printMatrix(d, n);
    cout << "Matrix LT =" << endl;
    printT_Matrix(l, n);
}

double matrix[maxN][maxN];

int main()
{
    int n = 3;
    double matrix[maxN][maxN] = {{13, -3, 4}, {-3, 20, 11}, {4, 11, 13}};
    if (!IsSymmetry(matrix, n))
    {
        cout << "Non-symmetry";
        return 0;
    }
    cout << fixed << setprecision(5);
    if (!PositiveDefinite(matrix, n))
        Cholesky(matrix, n);
    else
        classical_Cholesky(matrix, n);
    return 0;
}