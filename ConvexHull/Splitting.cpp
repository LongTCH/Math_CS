// Divide and Conquer
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
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
};
Point mid;

// determines the quadrant of a point
// (used in compare())
int quad(Point p)
{
    if (p.x >= 0 && p.y >= 0)
        return 1;
    if (p.x <= 0 && p.y >= 0)
        return 2;
    if (p.x <= 0 && p.y <= 0)
        return 3;
    return 4;
}

// Checks whether the line is crossing the polygon
int orientation(Point a, Point b,
                Point c)
{
    int res = (b.y - a.y) * (c.x - b.x) -
              (c.y - b.y) * (b.x - a.x);

    if (res == 0)
        return 0;
    if (res > 0)
        return 1;
    return -1;
}

// compare function for sorting
bool compare(const Point &p1, const Point &q1)
{
    Point p(p1.x - mid.x,
            p1.y - mid.y);
    Point q(q1.x - mid.x,
            q1.y - mid.y);

    int one = quad(p);
    int two = quad(q);

    if (one != two)
        return (one < two);
    return (p.y * q.x < q.y * p.x);
}

// Finds upper tangent of two polygons 'a' and 'b'
// represented as two vectors.
vector<Point> merger(vector<Point> a,
                     vector<Point> b)
{
    // n1 -> number of points in polygon a
    // n2 -> number of points in polygon b
    int n1 = a.size(), n2 = b.size();

    int ia = 0, ib = 0;
    for (int i = 1; i < n1; i++)
        if (a[i].x > a[ia].x)
            ia = i;

    // ib -> leftmost point of b
    for (int i = 1; i < n2; i++)
        if (b[i].x < b[ib].x)
            ib = i;

    // finding the upper tangent
    int inda = ia, indb = ib;
    bool done = 0;
    while (!done)
    {
        done = 1;
        while (orientation(b[indb], a[inda], a[(inda + 1) % n1]) >= 0)
            inda = (inda + 1) % n1;

        while (orientation(a[inda], b[indb], b[(n2 + indb - 1) % n2]) <= 0)
        {
            indb = (n2 + indb - 1) % n2;
            done = 0;
        }
    }

    int uppera = inda, upperb = indb;
    inda = ia, indb = ib;
    done = 0;
    int g = 0;
    while (!done) // finding the lower tangent
    {
        done = 1;
        while (orientation(a[inda], b[indb], b[(indb + 1) % n2]) >= 0)
            indb = (indb + 1) % n2;

        while (orientation(b[indb], a[inda], a[(n1 + inda - 1) % n1]) <= 0)
        {
            inda = (n1 + inda - 1) % n1;
            done = 0;
        }
    }

    int lowera = inda, lowerb = indb;
    vector<Point> ret;

    // ret contains the convex hull after merging the two convex hulls
    // with the points sorted in anti-clockwise order
    int ind = uppera;
    ret.push_back(a[uppera]);
    while (ind != lowera)
    {
        ind = (ind + 1) % n1;
        ret.push_back(a[ind]);
    }

    ind = lowerb;
    ret.push_back(b[lowerb]);
    while (ind != upperb)
    {
        ind = (ind + 1) % n2;
        ret.push_back(b[ind]);
    }
    return ret;
}

// Brute force algorithm to find convex hull for a set
// of less than 6 points
vector<Point> bruteHull(vector<Point> a)
{
    // Take any pair of points from the set and check
    // whether it is the edge of the convex hull or not.
    // if all the remaining points are on the same side
    // of the line then the line is the edge of convex
    // hull otherwise not
    set<Point> s;

    for (int i = 0; i < a.size(); i++)
    {
        for (int j = i + 1; j < a.size(); j++)
        {
            int x1 = a[i].x, x2 = a[j].x;
            int y1 = a[i].y, y2 = a[j].y;

            int a1 = y1 - y2;
            int b1 = x2 - x1;
            int c1 = x1 * y2 - y1 * x2;
            int pos = 0, neg = 0;
            for (int k = 0; k < a.size(); k++)
            {
                if (a1 * a[k].x + b1 * a[k].y + c1 <= 0)
                    neg++;
                if (a1 * a[k].x + b1 * a[k].y + c1 >= 0)
                    pos++;
            }
            if (pos == a.size() || neg == a.size())
            {
                s.insert(a[i]);
                s.insert(a[j]);
            }
        }
    }

    vector<Point> ret;
    for (auto e : s)
        ret.push_back(e);

    // Sorting the points in the anti-clockwise order
    mid = Point(0, 0);
    int n = ret.size();
    for (int i = 0; i < n; i++)
    {
        mid.x += ret[i].x;
        mid.y += ret[i].y;
        ret[i].x *= n;
        ret[i].y *= n;
    }
    sort(ret.begin(), ret.end(), compare);
    for (int i = 0; i < n; i++)
        ret[i] = Point(ret[i].x / n, ret[i].y / n);

    return ret;
}

// Returns the convex hull for the given set of points
vector<Point> divide(const vector<Point> &a)
{
    // If the number of points is less than 6 then the
    // function uses the brute algorithm to find the
    // convex hull
    if (a.size() <= 5)
        return bruteHull(a);

    // left contains the left half points
    // right contains the right half points
    vector<Point> left, right;
    for (int i = 0; i < a.size() / 2; i++)
        left.push_back(a[i]);
    for (int i = a.size() / 2; i < a.size(); i++)
        right.push_back(a[i]);

    // convex hull for the left and right sets
    vector<Point> left_hull = divide(left);
    vector<Point> right_hull = divide(right);

    // merging the convex hulls
    return merger(left_hull, right_hull);
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
    return labs(area / 2);
}
// Driver code
int main()
{
    vector<Point> points = {{6, 7}, {8, 6}, {9, 8}, {10, 9}, {11, 10}, {7, 12}, {6, 11}, {7, 11}, {10, 13}, {10, 7}};

    int n = points.size();

    // sorting the set of points according
    // to the x-coordinate
    sort(points.begin(), points.end());
    vector<Point> ans = divide(points);

    cout << "convex hull:\n";
    for (auto e : ans)
        cout << e << endl;
    cout << "Dien tich=" << area_polygon(ans);
    return 0;
}
