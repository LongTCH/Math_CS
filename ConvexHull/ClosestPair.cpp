#include <iostream>
#include <algorithm>
#include <cfloat>
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
    friend std::ostream &operator<<(std::ostream &os, const Point &p)
    {
        os << "(" << p.x << ", " << p.y << ")";
        return os;
    }
};

int compareX(const void *a, const void *b)
{
    Point *p1 = (Point *)a, *p2 = (Point *)b;
    return (p1->x - p2->x);
}

int compareY(const void *a, const void *b)
{
    Point *p1 = (Point *)a, *p2 = (Point *)b;
    return (p1->y - p2->y);
}
double dist(Point p1, Point p2)
{
    return sqrt((p1.x - p2.x) * (p1.x - p2.x) +
                (p1.y - p2.y) * (p1.y - p2.y));
}

pair<Point, Point> bruteForce(Point P[], int n)
{
    pair<Point, Point> closest;
    double min = DBL_MAX;
    for (int i = 0; i < n; ++i)
        for (int j = i + 1; j < n; ++j)
            if (dist(P[i], P[j]) < min)
            {
                min = dist(P[i], P[j]);
                closest = make_pair(P[i], P[j]);
            }
    return closest;
}

pair<Point, Point> stripClosest(Point strip[], int size, double d)
{
    double min = d; // Initialize the minimum distance as d
    pair<Point, Point> res;
    qsort(strip, size, sizeof(Point), compareY);
    for (int i = 0; i < size; ++i)
        for (int j = i + 1; j < size && (strip[j].y - strip[i].y) < min; ++j)
            if (dist(strip[i], strip[j]) < min)
            {
                min = dist(strip[i], strip[j]);
                res = make_pair(strip[i], strip[j]);
            }

    return res;
}
pair<Point, Point> closestUtil(Point P[], int n)
{
    if (n <= 3)
        return bruteForce(P, n);
    int mid = n / 2;
    Point midPoint = P[mid];
    pair<Point, Point> lp = closestUtil(P, mid);
    pair<Point, Point> rp = closestUtil(P + mid, n - mid);
    double dl = dist(lp.first, lp.second);
    double dr = dist(rp.first, rp.second);
    if (dr == 0)
        dr = DBL_MAX;
    double d = min(dl, dr);
    Point *strip = new Point[n];
    int j = 0;
    for (int i = 0; i < n; i++)
        if (fabs(P[i].x - midPoint.x) < d)
        {
            strip[j] = P[i];
            j++;
        }
    pair<Point, Point> p_ = stripClosest(strip, j, d);
    double d_ = dist(p_.first, p_.second);
    if (d_ == 0)
        d_ = DBL_MAX;
    if (d_ < d)
        return p_;
    if (dl == d)
        return lp;
    return rp;
}

pair<Point, Point> closest(Point P[], int n)
{
    qsort(P, n, sizeof(Point), compareX);
    return closestUtil(P, n);
}

int main()
{
    Point P[] = {{3, 6}, {4, 5}, {7, 7}, {8, 3}, {11, 9}, {7, 12}, {8, 10}, {7, 10}, {10, 12}, {8, 7}};
    int n = sizeof(P) / sizeof(P[0]);
    pair<Point, Point> res = closest(P, n);
    cout << "The closest pair is " << endl;
    cout << res.first << endl;
    cout << res.second << endl;
    return 0;
}
