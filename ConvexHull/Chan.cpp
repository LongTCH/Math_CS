// Shattering
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <algorithm>  // For qsort() algorithm
#include <utility>    // For pair() STL
#define RIGHT_TURN -1 // CW
#define LEFT_TURN 1   // CCW
#define COLLINEAR 0   // Collinear
using namespace std;
/*
Class to h&&le the 2D points!
*/
class Point
{
public:
    double x, y;
    Point(double newx = 0, double newy = 0)
    {
        x = newx;
        y = newy;
    }
    /*
        Overloaded == operator to check for equality between 2 objects of class Point
    */
    friend bool operator==(const Point &p1, const Point &p2)
    {
        return (p1.x == p2.x && p1.y == p2.y);
    }
    /*
        Overloaded != operator to check for non-equality between 2 objects of class Point
    */
    friend bool operator!=(const Point &p1, const Point &p2)
    {
        return (!(p1.x == p2.x && p1.y == p2.y));
    }
    /*
        Overloaded ostream << operator to check for print object of class Point to STDOUT
    */
    friend ostream &operator<<(ostream &output, const Point &p)
    {
        output << "(" << p.x << ", " << p.y << ")";
        return output;
    }
} p0; // Global Point class object

/*
    Returns square of the distance between the two Point class objects
    @param p1: Object of class Point aka first Point
    @param p2: Object of class Point aka second Point
*/
int dist(Point p1, Point p2)
{
    return (p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y);
}

/*
    Returns orientation of the line joining points p && q && line joining points q && r
    Returns -1 : CW orientation
            +1 : CCW orientation
            0 : Collinear
    @param p: Object of class Point aka first Point
    @param q: Object of class Point aka second Point
    @param r: Object of class Point aka third Point
*/
int orientation(Point p, Point q, Point r)
{
    int val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
    if (val == 0)
        return 0;              // Collinear
    return (val > 0) ? -1 : 1; // CW: -1 || CCW: 1
}

/*
    Predicate function used while sorting the points using qsort() inbuilt function in C++
    @param p: Object of class Point aka first Point
    @param p: Object of class Point aka second Point
*/
int compare(const void *vp1, const void *vp2)
{
    Point *p1 = (Point *)vp1;
    Point *p2 = (Point *)vp2;
    int orient = orientation(p0, *p1, *p2);
    if (orient == 0)
        return (dist(p0, *p2) >= dist(p0, *p1)) ? -1 : 1;
    return (orient == 1) ? -1 : 1;
}

/*
    Returns the index of the Point to which the tangent is drawn from Point p.
    Uses a modified Binary Search Algorithm to yield tangent in O(log n) complexity
    @param v: vector of objects of class points representing the hull aka the vector of hull points
    @param p: Object of class Point from where tangent needs to be drawn
*/
int tangent(vector<Point> v, Point p)
{
    int l = 0;
    int r = v.size();
    int l_before = orientation(p, v[0], v[v.size() - 1]);
    int l_after = orientation(p, v[0], v[(l + 1) % v.size()]);
    while (l < r)
    {
        int c = ((l + r) >> 1);
        int c_before = orientation(p, v[c], v[(c - 1) % v.size()]);
        int c_after = orientation(p, v[c], v[(c + 1) % v.size()]);
        int c_side = orientation(p, v[l], v[c]);
        if (c_before != RIGHT_TURN && c_after != RIGHT_TURN)
            return c;
        else if ((c_side == LEFT_TURN) && (l_after == RIGHT_TURN || l_before == l_after) || (c_side == RIGHT_TURN && c_before == RIGHT_TURN))
            r = c;
        else
            l = c + 1;
        l_before = -c_after;
        l_after = orientation(p, v[l], v[(l + 1) % v.size()]);
    }
    return l;
}

/*
    Returns the pair of integers representing the Hull # && the Point in that Hull which is the extreme amongst all given Hull Points
    @param hulls: Vector containing the hull points for various hulls stored as individual vectors.
*/
pair<int, int> extreme_hullpt_pair(vector<vector<Point>> &hulls)
{
    int h = 0, p = 0;
    for (int i = 0; i < hulls.size(); ++i)
    {
        int min_index = 0, min_y = hulls[i][0].y;
        for (int j = 1; j < hulls[i].size(); ++j)
        {
            if (hulls[i][j].y < min_y)
            {
                min_y = hulls[i][j].y;
                min_index = j;
            }
        }
        if (hulls[i][min_index].y < hulls[h][p].y)
        {
            h = i;
            p = min_index;
        }
    }
    return make_pair(h, p);
}

/*
    Returns the pair of integers representing the Hull # && the Point in that Hull to which the Point lpoint will be joined
    @param hulls: Vector containing the hull points for various hulls stored as individual vectors.
    @param lpoint: Pair of the Hull # && the leftmost extreme Point contained in that hull, amongst all the obtained hulls
*/
pair<int, int> next_hullpt_pair(vector<vector<Point>> &hulls, pair<int, int> lpoint)
{
    Point p = hulls[lpoint.first][lpoint.second];
    pair<int, int> next = make_pair(lpoint.first, (lpoint.second + 1) % hulls[lpoint.first].size());
    for (int h = 0; h < hulls.size(); h++)
    {
        if (h != lpoint.first)
        {
            int s = tangent(hulls[h], p);
            Point q = hulls[next.first][next.second];
            Point r = hulls[h][s];
            int t = orientation(p, q, r);
            if (t == RIGHT_TURN || (t == COLLINEAR) && dist(p, r) > dist(p, q))
                next = make_pair(h, s);
        }
    }
    return next;
}

/*
    Constraint to find the outermost boundary of the points by checking if the points lie to the left otherwise adding the given Point p
    Returns the Hull Points
    @param v: Vector of all the points
    @param p: New Point p which will be checked to be in the Hull Points || not
*/
vector<Point> keep_left(vector<Point> &v, Point p)
{
    while (v.size() > 1 && orientation(v[v.size() - 2], v[v.size() - 1], p) != LEFT_TURN)
        v.pop_back();
    if (!v.size() || v[v.size() - 1] != p)
        v.push_back(p);
    return v;
}

/*
    Graham Scan algorithm to find convex hull from the given set of points
    @param points: List of the given points in the cluster (as obtained by Chan's Algorithm grouping)
    Returns the Hull Points in a vector
*/
vector<Point> GrahamScan(vector<Point> &points)
{
    if (points.size() <= 1)
        return points;
    qsort(&points[0], points.size(), sizeof(Point), compare);
    vector<Point> lower_hull;
    for (int i = 0; i < points.size(); ++i)
        lower_hull = keep_left(lower_hull, points[i]);
    reverse(points.begin(), points.end());
    vector<Point> upper_hull;
    for (int i = 0; i < points.size(); ++i)
        upper_hull = keep_left(upper_hull, points[i]);
    for (int i = 1; i < upper_hull.size(); ++i)
        lower_hull.push_back(upper_hull[i]);
    return lower_hull;
}

/*
    Implementation of Chan's Algorithm to compute Convex Hull in O(nlogh) complexity
*/
vector<Point> chansalgorithm(vector<Point> v)
{
    for (int t = 0; t < v.size(); ++t)
    {
        for (int m = 1; m < (1 << (1 << t)); ++m)
        {
            vector<vector<Point>> hulls;
            for (int i = 0; i < v.size(); i = i + m)
            {
                vector<Point> chunk;
                if (v.begin() + i + m <= v.end())
                    chunk.assign(v.begin() + i, v.begin() + i + m);
                else
                    chunk.assign(v.begin() + i, v.end());
                hulls.push_back(GrahamScan(chunk));
            }

            vector<pair<int, int>> hull;
            hull.push_back(extreme_hullpt_pair(hulls));
            for (int i = 0; i < m; ++i)
            {
                pair<int, int> p = next_hullpt_pair(hulls, hull[hull.size() - 1]);
                vector<Point> output;
                if (p == hull[0])
                {
                    for (int j = 0; j < hull.size() - 1; ++j)
                    {
                        output.push_back(hulls[hull[j].first][hull[j].second]);
                    }
                    return output;
                }
                hull.push_back(p);
            }
        }
    }
    return {};
}

int main()
{
    vector<Point> points = {{0, 3.3}, {2, 2}, {1, 1}, {2, 1}, {3, 0}, {0, 0}, {3, 3}};
    vector<Point> output = chansalgorithm(points);
    cout << "\n---------After Using Chan's Algorithm---------------\n";
    cout << "\n***************** CONVEX HULL **********************\n";
    for (int i = 0; i < output.size(); ++i)
        cout << output[i] << endl;
    cout << "\n";
    return 0;
}