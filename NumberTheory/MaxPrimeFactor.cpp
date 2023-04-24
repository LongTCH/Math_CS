#include <iostream>
using namespace std;

// Function to check if a number is prime
bool isPrime(int n)
{
    if (n < 2)
        return false;
    for (int x = 2; x * x <= n; ++x)
    {
        if (n % x == 0)
            return false;
    }
    return true;
}

// Function to find the maximum prime factor of a given number
int maxPrimeFactor(int n)
{
    int maxFactor = 1;
    for (int i = 2; i * i <= n; i++)
    {
        if (n % i == 0)
        {
            if (isPrime(i))
            {
                maxFactor = i;
            }
            while (n % i == 0)
            {
                n /= i;
            }
        }
    }
    if (n > 1)
    {
        if (isPrime(n))
        {
            maxFactor = n;
        }
    }
    return maxFactor;
}

int main()
{
    int n;
    cout << "Enter a number: ";
    cin >> n;
    int maxFactor = maxPrimeFactor(n);
    cout << "The maximum prime factor of " << n << " is " << maxFactor << endl;
    return 0;
}
