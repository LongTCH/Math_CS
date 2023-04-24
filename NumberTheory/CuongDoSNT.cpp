#include <iostream>
#include <cmath>
using namespace std;

bool isPrime(int n)
{
    if (n <= 1)
    {
        return false;
    }
    for (int i = 2; i * i <= n; i++)
    {
        if (n % i == 0)
        {
            return false;
        }
    }
    return true;
}

int countPrimes(int n)
{
    int count = 0;
    for (int i = 2; i <= n; i++)
    {
        if (isPrime(i))
        {
            count++;
        }
    }
    return count;
}
double approximateDensePrime(const long long &n)
{
    return n / log(n);
}

int main()
{
    int n;
    cout << "Nhap mot so nguyen duong: ";
    cin >> n;
    cout << "Cuong do cua so nguyen to la: " << countPrimes(n) << endl;
    cout << "Xap xi Cuong do cua so nguyen to la: " << approximateDensePrime(n) << endl;
    return 0;
}