#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <queue>

using namespace std;

struct Point {
    int x, y;
};

Point min_left_point(vector<Point>& points) {
    Point cur_min{ 400, 400 };
    for (int i = 0; i < points.size(); i++) {
        if (points[i].y < cur_min.y || (points[i].y == cur_min.y && points[i].x < cur_min.x)) {
            cur_min = points[i];
        }
    }
    return cur_min;
}

int povorot(Point a, Point b, Point c) {
    float area = (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
    if (area < 0) return -1;
    else if (area == 0) return 0;
    else return 1;
}

double dist(Point a, Point b) {
    return sqrt(pow((a.x - b.x), 2) + pow((a.y - b.y), 2));
}

vector<Point> gift_wrapping(vector<Point>& points) {
    Point on_hull = min_left_point(points);
    vector<Point> hull;
    do {
        hull.push_back(on_hull);
        Point next_point = points[0];
        for (Point p : points) {
            int orientation = povorot(on_hull, next_point, p);
            if (orientation == -1 || (orientation == 0 && dist(on_hull, p) > dist(on_hull, next_point))) {
                next_point = p;
            }
        }
        on_hull = next_point;
    } while (!(on_hull.x == hull[0].x && on_hull.y == hull[0].y));
    return hull;
}

int main() {
    int NumberOfDots = 15;
    vector<Point> points;

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, 10);
    for (int i = 0; i < NumberOfDots; i++) {
        Point a;
        a.x = (int)dis(gen);
        a.y = (int)dis(gen);
        points.push_back(a);
    }
    vector<Point> convexHullPoints = gift_wrapping(points);
    cout << " points:" << endl;
    for (const Point& p : points) {
        cout << p.x << " " << p.y << endl;
    }
    std::cout << std::endl;
    cout << "convex hull points:" << endl;
    for (const Point& p : convexHullPoints) {
        cout << p.x << " " << p.y << endl;
    }
    return 0;
}