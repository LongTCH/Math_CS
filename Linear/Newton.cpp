#include <iostream>
#include <cmath>

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
    return 8 * x / pow(x * x + 10, 2) + 2 * (2 * x / (x * x + 10) + 1);
}

double newtonMethod(double guess, double epsilon, int maxIterations, double (*f)(double), double (*fPrime)(double))
{
    double x = guess;

    for (int i = 0; i < maxIterations; i++)
    {
        double fx = f(x);
        double fPrimeX = fPrime(x);
        double fDoublePrimeX = fDoublePrime(x);
        cout << i << ": "
             << "f(x) = " << f(x) << endl;
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
    double guess = 0.5;
    double epsilon = 1e-5;
    int maxIterations = 1000;

    double min = newtonMethod(guess, epsilon, maxIterations, f, fPrime);
    cout << min << endl;
    cout << "The minimum value of the function is: " << f(min) << endl;

    return 0;
}