#include <iostream>
using namespace std;
int gcd(int a, int b)
{
    while (b != 0)
    {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}
long long gcd(long long a, long long b)
{
    if (b == 0)
        return a;
    return gcd(b, a % b);
}
long long lcm(long long a, long long b)
{
    return (a * b) / (gcd(a, b));
}

int main()
{
    cout << gcd(20, 16) << endl;
    cout << lcm(20, 16) << endl;
}