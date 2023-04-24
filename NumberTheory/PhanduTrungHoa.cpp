#include <iostream>
#define MAX 100
using namespace std;
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
    // x = ai mod mi
    // Mi = Tich / mi
    // Mi*Ii = 1 mod mi
    int n = 4;
    int a[MAX] = {2, 4, 6, 8};
    int m[MAX] = {7, 9, 11, 13};
    for (int i = 0; i < n; ++i)
    {
        cout << "x = " << a[i] << " mod " << m[i] << endl;
    }
    cout << "Find x = " << solveCRT(a, m, n);
    return 0;
}