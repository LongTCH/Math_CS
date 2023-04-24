#include <iostream>
using namespace std;

const int MAX = 100000;
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
    for (int i = 0; i <= N; i++)
    {
        if (dem[i])
        {
            cout << i << "^" << dem[i] << " * ";
        }
    }
}