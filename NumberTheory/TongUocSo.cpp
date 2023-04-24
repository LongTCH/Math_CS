#include <iostream>
#include <math.h>
using namespace std;

const int MAX = 10000;
int dem[MAX];
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
    int res = 1;
    for (int i = 0; i <= N; i++)
    {
        if (dem[i])
        {
            res *= (pow(i, dem[i] + 1) - 1) / (i - 1);
        }
    }
    cout << res;
}