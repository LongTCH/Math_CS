#include <iostream>
#include <vector>
using namespace std;
int NearestPrime(int n)
{
    vector<bool> sieve(2 * n + 1, true);
    for (int i = 2; i * i <= 2 * n; ++i)
    {
        if (sieve[i])
        {
            for (int j = i * i; j <= 2 * n; j += i)
                sieve[j] = false;
        }
    }
    if (n % 2 == 0)
    {
        --n;
        if (sieve[n])
            return n;
    }
    int before = n - 2;
    int later = n + 2;
    int P = -1;
    while (P == -1)
    {
        if (sieve[before])
        {
            P = before;
            break;
        }
        else if (sieve[later])
        {
            P = later;
            break;
        }
        later += 2;
        before -= 2;
    }
    return P;
}
int main()
{
    cout << NearestPrime(144);
    return 0;
}