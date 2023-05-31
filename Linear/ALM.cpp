#include <iostream>
#include <cmath>
#include <iomanip>
using namespace std;
double f(double x1, double x2)
{
    return 6 * x1 * x1 + 4 * x1 * x2 + 3 * x2 * x2;
}
double findX1(double rk, double lamda)
{
    return (-90 * rk * rk + 9 * rk * lamda - 6 * lamda + 60 * rk) / ((14 - 5 * rk) * (12 + 2 * rk));
}
double findX2(double rk, double lamda)
{
    return (20 * rk - 2 * lamda) / (14 - 5 * rk);
}
double h(double x1, double x2)
{
    return x1 + x2 - 5;
}
void printMatrix(double rk, double lamda, double (*f)(double, double), double (*h)(double, double), double (*findX1)(double, double), double (*findX2)(double, double), double e)
{
    double _h = 1;
    do
    {
        double x1 = findX1(rk, lamda);
        double x2 = findX2(rk, lamda);
        _h = h(x1, x2);
        lamda += 2 * rk * _h;
        cout << lamda << setw(10) << right << rk << setw(10) << right << x1 << setw(10) << right << x2 << setw(10) << right << _h << endl;
    } while (fabs(_h) > e);
}
int main()
{
    cout << setprecision(5) << fixed;
    double e = 1e-5;
    double rk = 1;
    double lamda = 0;
    printMatrix(rk, lamda, f, h, findX1, findX2, e);
}