#include <iostream>
#include <iomanip>
using namespace std;

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

int main()
{
    int n = 2000, m = 100;
    int tong = 0;
    for (int i = m + 1; i < n; ++i)
        if (isPrime(i))
        {
            cout << setw(5) << i;
            tong += i;
        }
    cout << "\nTong la : " << tong;
}