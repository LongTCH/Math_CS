#include <iostream>
using namespace std;
int count_divisors(int N)
{
    int cnt = 0;
    for (int i = 1; i * i <= N; ++i)
        if (N % i == 0)
        {
            ++cnt;

            int j = N / i;
            if (j != i) // Cần xét trường hợp đặc biệt nếu N là số chính phương thì có thể i = j
                ++cnt;
        }

    return cnt;
}
int main()
{
    cout << count_divisors(10);
}