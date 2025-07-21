#pragma once
#include <cmath>

namespace compgeo {
namespace geometry {

struct Point {
  double x{}, y{};

  Point() = default;
  Point(double x_, double y_) : x(x_), y(y_) {}

  bool operator==(const Point &other) const {
    return x == other.x && y == other.y;
  }

  bool operator<(const Point &other) const {
    return (x < other.x) || (x == other.x && y < other.y);
  }

  static double cross(const Point &a, const Point &b, const Point &origin) {
    return (a.x - origin.x) * (b.y - origin.y) -
           (a.y - origin.y) * (b.x - origin.x);
  }
  static double distance(const Point &A, const Point &B) {
    double dx = A.x - B.x, dy = A.y - B.y;
    return dx * dx + dy * dy;
  }
};
} // namespace geometry
} // namespace compgeo
