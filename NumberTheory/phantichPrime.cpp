#include <iostream>
#include <vector>
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

int main()
{
    primeFactors(100);
}