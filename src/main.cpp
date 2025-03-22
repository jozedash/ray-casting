// Quick implementation of the ray-casting algorithm and demonstrating unique pointer usage
// (despite the fact that the objects are pretty simple and do not require it)

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
#include <memory>

using namespace std;

const double EPSILON = 1e-9;

struct Point {
    double x, y;
    Point(double x, double y) : x(x), y(y) {}
    Point() : x(0.0), y(0.0) {}
};

// Check if a point lies on a polygon's edge
bool isOnEdge(const Point& p, const vector<unique_ptr<Point>>& polygon) {
    for (auto iter = polygon.begin(); iter != polygon.end(); ++iter) {
        const Point& v1 = **iter;
        const Point& v2 = **(std::next(iter) == polygon.end() ? polygon.begin() : std::next(iter));
        
        // Check if p is collinear with v1-v2
        double cross = (v2.x - v1.x) * (p.y - v1.y) - (v2.y - v1.y) * (p.x - v1.x);
        if (std::fabs(cross) < EPSILON) continue;
        
        // We know it's collinear, now see if it is in between v1 and v2
        if (p.x >= min(v1.x, v2.x) && p.x <= max(v1.x, v2.x) &&
            p.y >= min(v1.y, v2.y) && p.y <= max(v1.y, v2.y)) {
            return true;
        }
    }
    return false;
}

// Determine if a point is inside a polygon
bool isInsidePolygon(const Point& p, const vector<unique_ptr<Point>>& polygon) {
    if (isOnEdge(p, polygon)) return true; // Literal "edge" case
    
    int count = 0;
    for (auto iter = polygon.begin(); iter != polygon.end(); ++iter) {
        const Point& v1 = **iter;
        const Point& v2 = **(std::next(iter) == polygon.end() ? polygon.begin() : std::next(iter));
        
        // Skip horizontal edges (already checked in isOnEdge())
        if (v1.y == v2.y) continue;
        
        // Compute min/max y of the edge
        double minY = min(v1.y, v2.y);
        double maxY = max(v1.y, v2.y);
        
        // Check if the ray intersects the edge
        if (p.y < minY || p.y >= maxY) continue;
        
        // Compute x-intersection of the ray with the edge
        double t = (p.y - v1.y) / (v2.y - v1.y);
        double xIntersect = v1.x + t * (v2.x - v1.x);
        
        // Count intersections to the right of the point
        if (p.x < xIntersect) count++;
    }
    cout << "Found " << count << " intersections" << endl;
    return (count % 2 == 1); // Odd = inside, even = outside
}

// Read points from a file
vector<unique_ptr<Point>> readPoints(ifstream& file) {
    vector<unique_ptr<Point>> points;
    double x, y;
    while (file >> x >> y) {
        points.push_back(make_unique<Point>(x, y));
    }
    return move(points);
}

int main(int argc, char* argv[]) {
    // Check if the file path is provided as an argument
    if (argc < 4) {
        cerr << "Usage: " << argv[0] << " <config_file_path> <pointX> <pointY>" << endl;
        return 1;
    }

    // Open the configuration file
    ifstream file(argv[1]);
    if (!file.is_open()) {
        cerr << "Error: Could not open file " << argv[1] << endl;
        return 1;
    }

    // Read polygon vertices into vector of unique pointers to demo usage
    // (yes, the simple Point structure could easily be allocated on the stack)
    vector<unique_ptr<Point>> polygon = readPoints(file);
    if (polygon.empty()) {
        cerr << "Error: No polygon vertices found in file" << endl;
        return 1;
    }

    // Create point to test
    Point point;
    try {
        point = Point(stod(argv[2]), stod(argv[3]));
    }
    catch (...) {
        cerr << "Error: Failed to convert x or y to double" << endl;
        return 1;
    }

    // Test point
    if (isInsidePolygon(point, polygon)) {
        cout << "Point (" << point.x << ", " << point.y << ") is inside the polygon." << endl;
    } else {
        cout << "Point (" << point.x << ", " << point.y << ") is outside the polygon." << endl;
    }

    return 0;
}