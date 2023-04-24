#include <iostream>
using namespace std;

void Sieve(long long n)
{
    bool sieve[100000];
    for (int i = 2; i <= n; ++i)
        sieve[i] = true;
    for (long long i = 2; i * i <= n; ++i)
    {
        if (sieve[i])
        {
            for (long long j = i * i; j <= n; j += i)
                sieve[j] = false;
        }
    }
    cout << "Prime numbers lower than or euqal to " << n << endl;
    for (long long i = 2; i <= n; ++i)
    {
        if (sieve[i])
            cout << i << " ";
    }
}
int main()
{
    Sieve(1000);
    return 0;
}