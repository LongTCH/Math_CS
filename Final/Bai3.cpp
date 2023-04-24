// Andrew
#include <iostream>
#include <algorithm>
#include <vector>
#include <cmath>
using namespace std;

class Point
{
public:
    double x, y;
    Point(double newx = 0, double newy = 0)
    {
        x = newx;
        y = newy;
    }
    bool operator<(const Point &other) const
    {
        return x < other.x || (x == other.x && y < other.y);
    }
    friend std::ostream &operator<<(std::ostream &os, const Point &p)
    {
        os << "(" << p.x << ", " << p.y << ")";
        return os;
    }
    double distanceTo(Point p)
    {
        return sqrt((p.x - this->x) * (p.x - this->x) + (p.y - this->y) * (p.y - this->y));
    }
};

int orientation(Point p, Point q, Point r)
{
    double val = (q.y - p.y) * (r.x - q.x) -
                 (q.x - p.x) * (r.y - q.y);

    if (val == 0)
        return 0;
    return (val > 0) ? 1 : 2;
}
vector<Point> convex_hull(vector<Point> points)
{
    int n = points.size();
    if (n < 3)
        return points;
    vector<Point> hull;
    int l = 0;
    for (int i = 1; i < n; i++)
        if (points[i].x < points[l].x)
            l = i;
    int p = l, q;
    do
    {
        hull.push_back(points[p]);
        q = (p + 1) % n;
        for (int i = 0; i < n; i++)
        {
            if (orientation(points[p], points[i], points[q]) == 2)
                q = i;
        }
        p = q;

    } while (p != l);
    return hull;
}

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
double area_polygon(const vector<Point> &vertices)
{
    double area = 0;
    int n = vertices.size();
    int j = n - 1;
    for (int i = 0; i < n; i++)
    {
        area += (vertices[i].x * vertices[j].y - vertices[j].x * vertices[i].y);
        j = i;
    }
    return fabs(area / 2);
}
// Driver code
int main()
{
    vector<Point> points = {{3, 6}, {4, 5}, {7, 7}, {8, 3}, {11, 9}, {7, 12}, {8, 10}, {7, 10}, {10, 12}, {8, 7}};

    // Find the convex hull
    vector<Point> ans = convex_hull(points);

    // Print the convex hull
    cout << "Cac dinh thuoc bao loi la: ";
    for (int i = 0; i < ans.size(); i++)
        cout << ans[i] << " ";
    cout << "\nDien tich bao loi la: " << area_polygon(ans);
    cout << "\nKhoang cach ngan nhat la: " << closestPair(ans);
    return 0;
}
