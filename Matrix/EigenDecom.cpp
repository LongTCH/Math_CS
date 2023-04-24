#include <iostream>
#include <iomanip>
#include "Eigen/Dense"
#include "Eigen/Eigenvalues"
using namespace std;
using namespace Eigen;

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
MatrixXd ToMatrixXd(Matrix A)
{
    MatrixXd res(A.size(), A[0].size());
    for (int i = 0; i < A.size(); i++)
        for (int j = 0; j < A[i].size(); j++)
            res(i, j) = A[i][j];
    return res;
}

Matrix ToMatrix(MatrixXd A)
{
    Matrix res(A.rows(), vector<double>(A.cols()));
    for (int i = 0; i < res.size(); i++)
        for (int j = 0; j < res[i].size(); j++)
            res[i][j] = A(i, j);
    return res;
}

void SwapCol(Matrix &A, int i, int j)
{
    for (int k = 0; k < A.size(); k++)
        swap(A[k][i], A[k][j]);
}
vector<Matrix> EigenDecompose(Matrix A)
{
    MatrixXd M = ToMatrixXd(A);
    EigenSolver<MatrixXd> S(M);
    Matrix P = ToMatrix(S.pseudoEigenvectors());
    Matrix G = ToMatrix(S.pseudoEigenvalueMatrix());
    for (int i = 0; i < G.size() - 1; i++)
        for (int j = i + 1; j < G.size(); j++)
            if (G[i][i] < G[j][j])
            {
                swap(G[i][i], G[j][j]);
                SwapCol(P, i, j);
            }
    return {P, G};
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
int main()
{
    cout << fixed << setprecision(5);
    Matrix A = {{13, -3, 4}, {-3, 20, 11}, {4, 11, 13}};
    cout << "Matrix A:" << endl;
    Print(A);
    vector<Matrix> res = EigenDecompose(A);
    Matrix EigenVectors = res[0];
    Matrix EigenValues = res[1];
    Matrix Inverse = matrix_inverse(EigenVectors);
    cout << "Matrix P:" << endl;
    Print(EigenVectors);
    cout << "Matrix D:" << endl;
    Print(EigenValues);
    cout << "Matrix P^-1:" << endl;
    Print(Inverse);
    cout << "Check: P * D * P^-1 = A:" << endl;
    Print(EigenVectors * EigenValues * Inverse);
    return 0;
}