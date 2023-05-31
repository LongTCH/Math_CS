#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <limits>
#include "Point.h"
using namespace std;

bool compare_y(const Point &p1, const Point &p2)
{
    return p1.y < p2.y;
}

pair<Point, Point> brute_force(vector<Point> &points, int start, int end)
{
    pair<Point, Point> closest;
    double min_distance = numeric_limits<double>::infinity();
    for (int i = start; i < end; ++i)
    {
        for (int j = i + 1; j < end; ++j)
        {
            double d = points[i].distanceTo(points[j]);
            if (d < min_distance)
            {
                min_distance = d;
                closest = make_pair(points[i], points[j]);
            }
        }
    }
    return closest;
}

pair<Point, Point> closest_pair_helper(vector<Point> &points, int start, int end)
{
    int n = end - start;
    if (n <= 3)
    {
        return brute_force(points, start, end);
    }
    int mid = start + n / 2;
    Point mid_point = points[mid];
    pair<Point, Point> left_pair = closest_pair_helper(points, start, mid);
    pair<Point, Point> right_pair = closest_pair_helper(points, mid, end);
    pair<Point, Point> closest = left_pair.second == right_pair.second
                                     ? left_pair
                                 : left_pair.first == mid_point
                                     ? make_pair(left_pair.second, right_pair.first)
                                 : right_pair.first == mid_point
                                     ? make_pair(left_pair.first, right_pair.second)
                                 : left_pair.first.distanceTo(left_pair.second) < right_pair.first.distanceTo(right_pair.second)
                                     ? left_pair
                                     : right_pair;
    double min_distance = closest.first.distanceTo(closest.second);
    vector<Point> strip;
    for (int i = start; i < end; ++i)
    {
        if (abs(points[i].x - mid_point.x) < min_distance)
        {
            strip.push_back(points[i]);
        }
    }
    sort(strip.begin(), strip.end(), compare_y);
    for (int i = 0; i < strip.size(); ++i)
    {
        for (int j = i + 1; j < strip.size() && strip[j].y - strip[i].y < min_distance; ++j)
        {
            double d = strip[i].distanceTo(strip[j]);
            if (d < min_distance)
            {
                min_distance = d;
                closest = make_pair(strip[i], strip[j]);
            }
        }
    }
    return closest;
}

pair<Point, Point> closest_pair(const vector<Point> &points)
{
    vector<Point> sorted_points = points;
    sort(sorted_points.begin(), sorted_points.end(), [](const Point &p1, const Point &p2)
         { return p1.x < p2.x || (p1.x == p2.x && p1.y < p2.y); });
    return closest_pair_helper(sorted_points, 0, sorted_points.size());
}

int main()
{
    vector<Point> points = {{0, 1}, {2, 2}, {1, 1}, {2, 1}, {3, 0}, {0, 0}, {3, 3}};
    pair<Point, Point> closest = closest_pair(points);
    cout << "(" << closest.first.x << ", " << closest.first.y << ") -> ("
         << closest.second.x << ", " << closest.second.y << ")" << endl;
    return 0;
}