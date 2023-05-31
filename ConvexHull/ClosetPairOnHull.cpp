#include <iostream>
#include <vector>
#include <math.h>
#include "Point.h"
using namespace std;
// Tìm cặp điểm có khoảng cách ngắn nhất trên bao lồi
pair<Point, Point> closestPairOnHull(vector<Point> &hull)
{
    int n = hull.size();
    if (n < 2)
        return make_pair(Point(), Point());

    double closest = hull[0].distanceTo(hull[n - 1]);
    pair<Point, Point> closestPair = make_pair(hull[0], hull[n - 1]);

    for (int i = 0; i < n - 1; i++)
    {
        double dist = hull[i].distanceTo(hull[i + 1]);
        if (dist < closest)
        {
            closest = dist;
            closestPair = make_pair(hull[i], hull[i + 1]);
        }
    }

    return closestPair;
}
int main()
{
    vector<Point> v = {{0, 3.3}, {3, 3}, {3, 0}, {0, 0}};
    auto ans = closestPairOnHull(v);
    cout << ans.first << " " << ans.second << endl;
    cout << ans.first.distanceTo(ans.second);
}