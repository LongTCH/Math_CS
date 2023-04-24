#include <iostream>
#include <math.h>
#include <vector>
using namespace std;

int phiEuler(int N)
{
    int n = N;
    vector<int> dem(n, 0);
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
    long long res = 1;
    for (int i = 2; i <= N; i++)
    {
        if (dem[i] != 0)
        {
            res *= pow(i, dem[i] - 1) * (i - 1);
        }
    }
    return res;
}
int main()
{
    cout << phiEuler(12);
}