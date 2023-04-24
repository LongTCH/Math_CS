#include <iostream>
using namespace std;
typedef unsigned long long ull;

// a ^ b mod m
ull modPow(ull a, ull b, ull m)
{
    if (b == 0)
        return 1 % m;
    ull u = modPow(a, b / 2, m);
    u = (u * u) % m;
    if (b % 2 == 1)
    {
        u = (u * a) % m;
    }
    return u;
}

int main()
{
    // test;
    cout << modPow(100, 200, 99);
}
