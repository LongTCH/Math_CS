#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>
using namespace std;

#define Matrix vector<vector<double>>

void Print(Matrix A)
{
    for (int i = 0; i < A.size(); i++)
    {
        for (int j = 0; j < A[i].size(); j++)
            cout << setw(10) << A[i][j] << "\t";
        cout << endl;
    }
}
Matrix operator*(Matrix a, Matrix b)
{
    Matrix c;
    if (a[0].size() != b.size())
        return c;
    c = Matrix(a.size(), vector<double>(b[0].size(), 0));
    for (int i = 0; i < c.size(); i++)
        for (int j = 0; j < c[i].size(); j++)
            for (int k = 0; k < b.size(); k++)
                c[i][j] += a[i][k] * b[k][j];
    return c;
}

void SwapCol(Matrix &A, int i, int j)
{
    for (int k = 0; k < A.size(); k++)
        swap(A[k][i], A[k][j]);
}
Matrix matrix_inverse(const Matrix &mat)
{
    int n = mat.size();

    // Create a copy of the input matrix
    Matrix A(mat);

    // Create an identity matrix
    Matrix inv(n, vector<double>(n));
    for (int i = 0; i < n; i++)
    {
        inv[i][i] = 1;
    }

    // Gaussian elimination to reduce the matrix to row echelon form
    for (int i = 0; i < n; i++)
    {
        // Find the pivot element
        double pivot = A[i][i];
        int pivot_row = i;
        for (int j = i + 1; j < n; j++)
        {
            if (abs(A[j][i]) > abs(pivot))
            {
                pivot = A[j][i];
                pivot_row = j;
            }
        }

        // Swap the rows if necessary
        if (pivot_row != i)
        {
            swap(A[i], A[pivot_row]);
            swap(inv[i], inv[pivot_row]);
        }

        // Reduce the matrix to row echelon form
        for (int j = i + 1; j < n; j++)
        {
            double multiplier = A[j][i] / A[i][i];
            for (int k = i + 1; k < n; k++)
            {
                A[j][k] -= multiplier * A[i][k];
            }
            for (int k = 0; k < n; k++)
            {
                inv[j][k] -= multiplier * inv[i][k];
            }
        }
    }

    // Back-substitution to reduce the matrix to reduced row echelon form
    for (int i = n - 1; i >= 0; i--)
    {
        for (int j = i - 1; j >= 0; j--)
        {
            double multiplier = A[j][i] / A[i][i];
            for (int k = 0; k < n; k++)
            {
                inv[j][k] -= multiplier * inv[i][k];
            }
        }
    }

    // Divide each row by the diagonal element to obtain the inverse
    for (int i = 0; i < n; i++)
    {
        double diagonal_element = A[i][i];
        for (int j = 0; j < n; j++)
        {
            inv[i][j] /= diagonal_element;
        }
    }

    return inv;
}
Matrix GetIMatrix(int n)
{
    Matrix m(n, vector<double>(n, 0));
    for (int i = 0; i < n; ++i)
        m[i][i] = 1;
    return m;
}
Matrix MatrixPow(const Matrix &mat, int p)
{
    Matrix A = GetIMatrix(mat.size());
    Matrix M(mat);
    while (p)
    {
        if (p % 2)
            A = A * M;
        M = M * M;
        p /= 2;
    }
    return A;
}
int main()
{
    cout << fixed << setprecision(5);
    int T = 2, s = 0, f = 0;
    Matrix A = {{0.28, 0.72}, {0.79, 0.21}};
    Matrix res = MatrixPow(A, T);
    // Print(res);
    cout << "Xac xuat lon nhat sau " << T << " giai doan van hanh he thong lam viec o trang thai " << f
         << " \nbiet bat dau la trang thai " << s << " : " << res[s][f];
    return 0;
}
