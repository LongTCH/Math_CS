#include <iostream>
#include <math.h>
using namespace std;

const int MAX = 10000;
int dem[MAX];
int numberOfFactors(int n)
{
    int res = 1;
    for (int i = 2; i <= n; i++)
    {
        res *= (dem[i] + 1);
    }
    return res;
}
int main()
{
    int N;
    cout << "\nNhap n = ";
    cin >> N;
    int n = N; // Tao ban sao cua N
    for (int i = 0; i <= n; i++)
        dem[i] = 0;
    for (int i = 2; i <= n; i++)
    {
        while (n % i == 0)
        {
            ++dem[i];
            n /= i;
        }
    }
    long long res = pow(N, numberOfFactors(N) * 1.0 / 2);
    cout << res;
}