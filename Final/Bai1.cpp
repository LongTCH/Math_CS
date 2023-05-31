#include <iostream>
#include <vector>
#define MAX 100
using namespace std;
void primeFactors(int n)
{
    cout << "Phan tich ra thua so nguyen to voi n = " << n << " la: ";
    vector<pair<int, int>> factors;
    int d = 2;
    while (n > 1)
    {
        int count = 0;
        while (n % d == 0)
        {
            n /= d;
            count++;
        }
        if (count > 0)
        {
            factors.push_back(make_pair(d, count));
        }
        d++;
    }
    for (int i = 0; i < factors.size(); ++i)
    {
        cout << factors[i].first << "^" << factors[i].second;
        if (i != factors.size() - 1)
            cout << " * ";
    }
}

void Sieve(int n)
{
    bool sieve[100000];
    for (int i = 2; i <= n; ++i)
        sieve[i] = true;
    for (int i = 2; i * i <= n; ++i)
    {
        if (sieve[i])
        {
            for (int j = i * i; j <= n; j += i)
                sieve[j] = false;
        }
    }
    int res = 0;
    cout << "Cac so nguyen to nho hon " << n << endl;
    for (int i = 2; i < n; ++i)
    {
        if (sieve[i])
        {
            cout << i << " ";
            res += i;
        }
    }
    cout << "\nTong cua chung la: " << res;
}
int modInverse(int &M, int &m)
{
    int k = 0;
    while ((k * m + 1) % M != 0)
    {
        ++k;
    }
    return (k * m + 1) / M;
}
int solveCRT(int rem[], int mod[], int n)
{
    int M = 1;
    int x = 0;

    // Compute product of all moduli
    for (int i = 0; i < n; i++)
    {
        M *= mod[i];
    }

    for (int i = 0; i < n; i++)
    {
        // Compute the factor Mi
        int Mi = M / mod[i];

        // Compute the modular inverse of Mi
        int Mi_inv = modInverse(Mi, mod[i]);

        // Update x with the current congruence
        x += rem[i] * Mi * Mi_inv;
    }

    return x % M;
}
int main()
{
    cout << "Cau 1a:" << endl;
    primeFactors(26000);
    cout << endl;
    Sieve(90);
    cout << "\nCau 1b:" << endl;
    // x = ai mod mi
    // Mi = Tich / mi
    // Mi*Ii = 1 mod mi
    int n = 4;
    int a[MAX] = {2, 3, 4, 5};
    int m[MAX] = {3, 5, 7, 11};
    for (int i = 0; i < n; ++i)
    {
        cout << "x = " << a[i] << " mod " << m[i] << endl;
    }
    cout << "Find x = " << solveCRT(a, m, n);
}