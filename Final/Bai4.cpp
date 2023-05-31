#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
using namespace std;
double _f(double x)
{
    return pow(exp(2 * x) - 2 * x * x - 5 * pow(x, 5), 2) + 2 * pow(x, 4);
}
double derivative_f_1(double x)
{
    return 2 * (exp(2 * x) - 2 * x * x - 5 * pow(x, 5)) * (2 * exp(2 * x) - 4 * x - 25 * pow(x, 4)) + 8 * pow(x, 3);
}
double fDoublePrime(double x)
{
    return 2 * pow(2 * exp(2 * x) - 4 * x - 25 * pow(x, 4), 2) + 2 * (exp(2 * x) - 2 * x * x - 5 * pow(x, 5)) * (4 * exp(2 * x) - 4 - 100 * pow(x, 3)) + 24 * x * x;
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

double newtonMethod(double guess, int maxIterations, double epsilon, double (*f)(double), double (*fPrime)(double), double (*fDoublePrime)(double))
{
    double x = guess;

    for (int i = 0; i < maxIterations; i++)
    {
        double fx = f(x);
        double fPrimeX = fPrime(x);
        double fDoublePrimeX = fDoublePrime(x);
        if (fabs(fPrimeX) < epsilon)
        {
            break;
        }
        x = x - fPrimeX / fDoublePrimeX;
    }

    return x;
}
int main()
{
    double learningRate = 0.01, alpha = 0.1, x = -0.5;
    cout << "Gia tri nho nhat cua ham so su dung GD la: ";
    cout << _f(gradientDescent(x, learningRate, 1000, 1e-5, _f, derivative_f_1)) << endl;
    cout << "Gia tri nho nhat cua ham so su dung GD with Momentum la: ";
    cout << _f(GradientDescentMomentum(x, alpha, learningRate, 1000, 1e-5, _f, derivative_f_1)) << endl;
    cout << "Gia tri nho nhat cua ham so su dung Newton Method la: ";
    cout << _f(newtonMethod(x, 1000, 1e-5, _f, derivative_f_1, fDoublePrime));
}