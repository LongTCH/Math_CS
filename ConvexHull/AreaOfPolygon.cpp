#include <iostream>
#include <vector>
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
};

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

int main()
{
    vector<Point> vertices = {{0, 1}, {2, 3}, {4, 7}};
    double area = area_polygon(vertices);
    cout << "Area of polygon = " << area << endl;
    return 0;
}
