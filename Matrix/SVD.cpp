#include <iostream>
#include <iomanip>
#include "Eigen/Dense"
#include "Eigen/Eigenvalues"
using namespace std;
using namespace Eigen;

#define Vector vector<double>
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
void PrintValue(Matrix A)
{
	for (int i = 0; i < A.size(); i++)
	{
		cout << setw(10) << A[i][i] << "\t";
	}
	cout << endl;
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
	Matrix res(A.rows(), Vector(A.cols()));
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

Vector FillMatrixU(Matrix A)
{
	for (int i = 0; i < A.size(); i++)
	{
		int i_m = i, v_m = A[i][i];
		for (int j = i + 1; j < A.size(); j++)
			if (abs(A[j][i] > v_m))
			{
				v_m = A[j][i];
				i_m = j;
			}
		if (i_m != i)
			swap(A[i], A[i_m]);
		for (int j = i + 1; j < A.size(); j++)
		{
			double f = 0;
			if (A[i][i] != 0)
				f = A[j][i] / A[i][i];
			for (int k = i + 1; k < A[j].size(); k++)
				A[j][k] -= A[i][k] * f;
			A[j][i] = 0;
		}
	}
	for (int i = 0; i < A.size(); i++)
		for (int j = 0; j < A.size(); j++)
			if (isnan(A[i][j]))
				A[i][j] = 0;
	Vector X(A.size(), 1);
	for (int i = 0; i < A.size(); i++)
	{
		int j;
		bool f = false;
		for (j = 0; j < A.size(); j++)
			if (A[i][j] != 0)
			{
				f = true;
				break;
			}
		if (f)
			X[j] = -i;
	}
	for (int i = X.size() - 1; i >= 0; i--)
		if (X[i] <= 0)
		{
			int r = -X[i];
			X[i] = 0;
			for (int j = i + 1; j < A[r].size(); j++)
				X[i] -= X[j] * A[r][j] / A[r][i];
		}
	double s = 0;
	for (int i = 0; i < X.size(); i++)
		s += X[i] * X[i];
	for (int i = 0; i < X.size(); i++)
		X[i] /= sqrt(s);
	return X;
}
Matrix Tranpose(Matrix A)
{
	Matrix res(A[0].size(), Vector(A.size()));
	for (int i = 0; i < A.size(); i++)
		for (int j = 0; j < A[i].size(); j++)
			res[j][i] = A[i][j];
	return res;
}
Matrix operator*(Matrix a, Matrix b)
{
	Matrix c;
	if (a[0].size() != b.size())
		return c;
	c = Matrix(a.size(), Vector(b[0].size(), 0));
	for (int i = 0; i < c.size(); i++)
		for (int j = 0; j < c[i].size(); j++)
			for (int k = 0; k < b.size(); k++)
				c[i][j] += a[i][k] * b[k][j];
	return c;
}
vector<Matrix> SVDDecompose(Matrix A)
{
	Matrix AT = Tranpose(A);
	Matrix P = AT * A;
	vector<Matrix> Holder = EigenDecompose(P);
	cout << "Matrix AT:" << endl;
	Print(AT);
	cout << "Matrix AT * A:" << endl;
	Print(P);
	cout << "Eigen Values" << endl;
	PrintValue(Holder[1]);
	cout << "Eigen Vector" << endl;
	Print(Holder[0]);
	Matrix V = Holder[0];
	Matrix D(A.size(), Vector(A[0].size()));
	for (int i = 0; i < min(Holder[1].size(), D.size()); i++)
		for (int j = 0; j < min(Holder[1][i].size(), D[i].size()); j++)
		{
			D[i][j] = sqrt(Holder[1][i][j]);
			if (isnan(D[i][j]))
				D[i][j] = 0;
		}
	Matrix U = A * V;
	while (U[0].size() < A.size())
		for (int i = 0; i < U.size(); i++)
			U[i].push_back(0);
	while (U[0].size() > A.size())
		for (int i = 0; i < U.size(); i++)
			U[i].pop_back();
	for (int i = 0; i < U.size(); i++)
	{
		if (D[i][i] != 0)
			for (int j = 0; j < U.size(); j++)
				U[j][i] /= D[i][i];
		else
			for (int j = 0; j < U.size(); j++)
				U[j][i] /= D[i][i];
	}
	for (int i = 0; i < U.size(); i++)
	{
		if (i < min(D.size(), D[0].size()) && D[i][i] != 0)
			continue;
		Vector v = FillMatrixU(Tranpose(U));
		for (int j = 0; j < U.size(); j++)
			U[j][i] = v[j];
	}
	return {U, D, Tranpose(V)};
}

int main()
{
	cout << fixed << setprecision(5);
	Matrix A = {{1, 1}, {0, 1}, {-1, 1}};
	cout << "Matrix A:" << endl;
	Print(A);
	vector<Matrix> SVD = SVDDecompose(A);
	cout << "Matrix U:" << endl;
	Print(SVD[0]);
	cout << "Matrix Sigma:" << endl;
	Print(SVD[1]);
	cout << "Matrix VT:" << endl;
	Print(SVD[2]);
	cout << "Check: U * Sigma * VT = A" << endl;
	Print(SVD[0] * SVD[1] * SVD[2]);
	return 0;
}
/*
Để phân rã một ma trận A thành tích ba ma trận U, Σ và V^T, ta cần thực hiện các bước sau:
1. Tính A^T A: Tính ma trận A^T A có kích thước n x n, trong đó n là số cột của A. Đây là bước tính toán đầu tiên và có độ phức tạp O(n^2 m).
2. Tính phép phân rã trực giao cho ma trận A^T A: Sử dụng một thuật toán phân rã trực giao như phép phân rã QR hoặc phương pháp lặp (power iteration) để tính ma trận trực giao V có kích thước n x n và ma trận đường chéo Sigma có kích thước n x n. Độ phức tạp của bước này phụ thuộc vào thuật toán phân rã trực giao được sử dụng, nhưng thường là O(n^3).
3. Tính ma trận U: Sử dụng các thông tin từ bước 2 để tính ma trận U. Nếu ta muốn tính toán tất cả các cột của U, thì ta thực hiện tính toán u_i = (1/sigma_i) * A * v_i với i = 1,2,…,n, trong đó v_i là cột thứ i của ma trận V, sigma_i là phần tử trên đường chéo thứ i của ma trận Sigma, và u_i là cột thứ i của ma trận U. Độ phức tạp của bước này là O(n^2 m). Kết quả: Sau khi tính được ma trận U, Sigma, và V, ta có thể viết lại ma trận A dưới dạng tích của ba ma trận này: A = U * Sigma * V^T. Tổng độ phức tạp của phân rã SVD là O(n^3), do bước tính ma trận A^T A và bước tính ma trận U có độ phức tạp cao nhất.
*/