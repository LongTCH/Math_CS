#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
using namespace std;
double _f(double x)
{
    return pow(exp(2 * x * x + 1) - 2 * x + 1, 2) - 5 * pow(x + 1, 3);
}
double derivative_f_1(double x)
{
    return 2 * (exp(2 * x * x + 1) - 2 * x + 1) * (4 * x * exp(2 * x * x + 1) - 2) - 15 * pow(x + 1, 2);
}
double gradientDescent(double startPoint, double learningRate, int Loop, double e, double (*f)(double), double (*fPrime)(double))
{
    double back, curr;
    back = startPoint;
    int i;
    for (i = 1; i <= Loop; i++)
    {
        curr = back - learningRate * fPrime(back);
        if (fabs(fPrime(curr)) < e)
        {
            break;
        }
        back = curr;
    }
    return curr;
}
double GradientDescentMomentum(double startPoint, double alpha, double learningRate, int Loop, double epsilon, double (*f)(double), double (*fPrime)(double))
{
    double back, curr;
    double deltaX = 0;
    double newDeltaX;
    back = startPoint;
    int i;
    for (i = 1; i <= Loop; i++)
    {
        newDeltaX = deltaX * alpha - fPrime(back) * learningRate;
        curr = back + alpha * newDeltaX - learningRate * fPrime(back);
        deltaX = newDeltaX;
        if (fabs(fPrime(curr)) < epsilon)
        {
            break;
        }
        back = curr;
    }
    return curr;
}

int main()
{
    cout << "Gia tri nho nhat cua ham so su dung GD la: ";
    cout << _f(gradientDescent(0.2, 0.01, 1000, 1e-5, _f, derivative_f_1)) << endl;
    cout << "Gia tri nho nhat cua ham so su dung GD with Momentum la: ";
    cout << _f(GradientDescentMomentum(0.2, 0.01, 0.01, 1000, 1e-5, _f, derivative_f_1));
}