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

int main()
{
    cout << gradientDescent(0.5, 0.01, 1000, 1e-5, f, fPrime);
}