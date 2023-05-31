#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include "Point.h"
using namespace std;
pair<Point, Point> closestPair(vector<Point> P)
{
    double upper_b = 999999999;
    pair<Point, Point> ans;
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
            double temp = P[i].distanceTo(P[j]);
            if (upper_b > temp)
            {
                upper_b = temp;
                ans = make_pair(P[i], P[j]);
            }
            j--;
        }
        j = i + 1;
        while (j < P.size() && abs(P[i].y - P[j].y) <= upper_b)
        {
            double temp = P[i].distanceTo(P[j]);
            if (upper_b > temp)
            {
                upper_b = temp;
                ans = make_pair(P[i], P[j]);
            }
            j++;
        }
    }
    return ans;
}
int main()
{
    vector<Point> P{{3, 6}, {4, 5}, {7, 7}, {8, 3}, {11, 9}, {7, 12}, {8, 10}, {7, 10}, {10, 12}, {8, 7}};
    auto ans = closestPair(P);
    cout << ans.first << " " << ans.second << endl;
    cout << ans.first.distanceTo(ans.second);
}
