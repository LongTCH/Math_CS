#include <iostream>
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
    friend ostream &operator<<(ostream &os, const Point &p)
    {
        os << "(" << p.x << ", " << p.y << ")";
        return os;
    }
    double distanceTo(Point p)
    {
        return sqrt((p.x - this->x) * (p.x - this->x) + (p.y - this->y) * (p.y - this->y));
    }
    friend bool operator==(const Point &p1, const Point &p2)
    {
        return (p1.x == p2.x && p1.y == p2.y);
    }
    friend bool operator!=(const Point &p1, const Point &p2)
    {
        return (!(p1.x == p2.x && p1.y == p2.y));
    }
};
/*
    Returns orientation of the line joining points p && q && line joining points q && r
    Returns -1 : CW orientation
            +1 : CCW orientation
            0 : Collinear
    @param p: Object of class Point aka first Point
    @param q: Object of class Point aka second Point
    @param r: Object of class Point aka third Point
*/
int orientation(const Point &p, const Point &q, const Point &r)
{
    int val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
    if (val == 0)
        return 0;
    return (val > 0) ? -1 : 1;
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