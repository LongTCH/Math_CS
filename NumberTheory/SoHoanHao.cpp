#include <iostream>
using namespace std;

bool isPerfect(int num)
{
    if (num == 1)
        return false;
    int sum = 1;
    for (int i = 2; i * i <= num; i++)
    {
        if (num % i == 0)
        {
            sum += i;
            if (i != num / i)
            {
                sum += num / i;
            }
        }
    }
    return (sum == num);
}

int main()
{
    int n;
    cout << "Nhap mot so nguyen duong: ";
    cin >> n;
    if (isPerfect(n))
    {
        cout << n << " la so hoan hao." << endl;
    }
    else
    {
        cout << n << " khong phai la so hoan hao." << endl;
    }
    return 0;
}
