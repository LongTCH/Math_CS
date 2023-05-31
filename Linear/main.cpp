#include <iostream>
#include <math.h>
using namespace std;
double f(double x)
{
    return pow(log(x * x + 10) + x - 5, 2) + 2 * x;
}
double fPrime(double x)
{
    return 2 * (log(x * x + 10) + x - 5) * (2 * x / (x * x + 10) + 1) + 2;
}
double fDoublePrime(double x)
{
    return (2 * x / (x * x + 10) + 1) * (4 * x / (x * x + 10) + 2) + (log(x * x + 10) + x - 5) * ((40 - 4 * x * x) / pow(x * x + 10, 2));
}
double g(double x)
{
    return pow(log(x * x + 15) + x - 15, 2) + x;
}
double gPrime(double x)
{
    return 2 * (log(x * x + 15) + x - 15) * (2 * x / (x * x + 15) + 1) + 1;
}
double gDoublePrime(double x)
{
    return (2 * x / (x * x + 15) + 1) * (4 * x / (x * x + 15) + 2) + (log(x * x + 15) + x - 15) * ((60 - 4 * x * x) / pow(x * x + 15, 2));
}
double gradientDescent(double startPoint, double learningRate, int Loop, double e, double (*fPrime)(double))
{
    double back, curr;
    back = startPoint;
    int i;
    for (i = 1; i <= Loop; i++)
    {
        curr = back - learningRate * fPrime(back);
        // cout << i << ": "
        //      << "f(x) = " << f(back) << endl;
        if (fabs(fPrime(curr)) < e)
        {
            break;
        }
        back = curr;
    }
    return curr;
}
double GradientDescentMomentum(double startPoint, double alpha, double learningRate, double epsilon, int Loop, double (*fPrime)(double))
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
        // cout << i << ": "
        //      << "f(x) = " << f(back) << endl;
        if (fabs(fPrime(curr)) < epsilon)
        {
            break;
        }
        back = curr;
    }
    return curr;
}
double newtonMethod(double guess, double epsilon, int maxIterations, double (*fPrime)(double), double (*fDoublePrimeX)(double))
{
    double x = guess;

    for (int i = 0; i < maxIterations; i++)
    {
        double fx = f(x);
        double fPrimeX = fPrime(x);
        double fDoublePrimeX = fDoublePrime(x);
        // cout << i << ": "
        //      << "f(x) = " << f(x) << endl;
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
    double e = 1e-5;
    int Loop = 1000;
    double learningRate = 0.1;
    double momentum = 0.9;
    double x0_f = 0.5;
    double x0_g = 7;
    cout << "Min f(x)" << endl;
    cout << "Gradient Descent: " << f(gradientDescent(x0_f, learningRate, Loop, e, fPrime)) << endl;
    cout << "Gradient Decent With Momentum: " << f(GradientDescentMomentum(x0_f, momentum, learningRate, e, Loop, fPrime)) << endl;
    cout << "Newton: " << f(newtonMethod(x0_f, e, Loop, fPrime, fDoublePrime)) << endl;
    cout << "Min g(x)" << endl;
    cout << "Gradient Descent: " << g(gradientDescent(x0_g, learningRate, Loop, e, gPrime)) << endl;
    cout << "Gradient Decent With Momentum: " << g(GradientDescentMomentum(x0_g, momentum, learningRate, e, Loop, gPrime)) << endl;
    cout << "Newton: " << g(newtonMethod(x0_g, e, Loop, gPrime, gDoublePrime)) << endl;
}