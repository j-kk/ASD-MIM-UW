#include <cstdio>
#include <queue>
#include <algorithm>
#include <stdlib.h>
using namespace std;

const int MAXN = 200000;
const int MAXCORD = 1000000000;

struct Point {
    int id;
    int x, y, d;
    Point(int id, int x, int y, int d):
    id(id), x(x), y(y), d(d) {}
};

int n;
vector<Point> points;
class Compare {
public:
    bool operator() (Point a, Point b) {
        return a.d > b.d;
    }
};
bool cmpX (Point a, Point b) {
    return a.x < b.x;
}

bool cmpY (Point a, Point b) {
    return a.y < b.y;
}

bool cmpID (Point a, Point b) {
    return a.id < b.id;
}

int calcDist(Point a, Point b) {
    return min(abs(a.x - b.x), abs(a.y - b.y));
}

void constructGraph(vector<vector<Point>> &rows, bool cmp(Point a, Point b)) {
    sort(points.begin(), points.end(), cmp);
    
    Point &north = points.at(1);
    rows.at(points.at(0).id).push_back(north);
    
    Point &south = points.at(n - 2);
    rows.at(points.at(n - 1).id).push_back(south);
    
    for (int i = 1; i < n - 1; ++i) {
        Point &south = points.at(i - 1);
        rows.at(points.at(i).id).emplace_back(south);
        Point &north = points.at(i + 1);
        rows.at(points.at(i).id).emplace_back(north);
    }
}

int main() {
    scanf ("%d", &n);
    
    for(int i = 0 ; i < n; ++i) {
        int x, y;
        scanf ("%d %d", &x, &y);
        points.emplace_back(i, x, y, MAXCORD);
    }
    
    vector<vector<Point>> rows(n, vector<Point>());
    Point &start = points.at(0);
    Point &finish = points.at(n - 1);
    
    constructGraph(rows, cmpX);
    constructGraph(rows, cmpY);
    
    sort(points.begin(), points.end(), cmpID);
    start.d = 0;
    
    priority_queue<Point, vector<Point>, Compare> q;
    q.push(start);
    
    while (!q.empty()) {
        Point actual = q.top();
        q.pop();
        
        for (int i = 0; i < rows.at(actual.id).size(); ++i) {
            Point &t = points.at(rows.at(actual.id).at(i).id);
            if (t.d > actual.d + calcDist(t, actual)) {
                t.d = actual.d + calcDist(t, actual);
                q.push(t);
            }
        }
        
        
    }
    
    printf("%d\n", finish.d);
    
    return 0;
}
