#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;
class Point
{
public:
    double x, y;
    Point(double x = 0, double y = 0)
    {
        this->x = x;
        this->y = y;
    }
    double distanceTo(Point p)
    {
        return sqrt((p.x - this->x) * (p.x - this->x) + (p.y - this->y) * (p.y - this->y));
    }
};
double closestPair(vector<Point> P)
{
    double upper_b = 999999999;

    sort(P.begin(), P.end(), [](Point a, Point b)
         { return a.x < b.x; });
    for (int i = 0; i < P.size() - 1; i++)
        upper_b = min(upper_b, P[i].distanceTo(P[i + 1]));
    sort(P.begin(), P.end(), [](Point a, Point b)
         { return a.y < b.y; });
    for (int i = 0; i < P.size(); i++)
    {
        int j = i - 1;
        while (j >= 0 && abs(P[i].y - P[j].y) <= upper_b)
        {
            upper_b = min(upper_b, P[i].distanceTo(P[j]));
            j--;
        }
        j = i + 1;
        while (j < P.size() && abs(P[i].y - P[j].y) <= upper_b)
        {
            upper_b = min(upper_b, P[i].distanceTo(P[j]));
            j++;
        }
    }
    return upper_b;
}
int main()
{
    vector<Point> P{{3, 6}, {4, 5}, {7, 7}, {8, 3}, {11, 9}, {7, 12}, {8, 10}, {7, 10}, {10, 12}, {8, 7}};
    cout << closestPair(P);
}
