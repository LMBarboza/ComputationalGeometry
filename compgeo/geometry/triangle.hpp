#pragma once

#include "point.hpp"
#include <tuple>
namespace compgeo {
namespace geometry {

struct Triangle {
  std::tuple<Point, Point, Point> a, b, c;

  static double triangle_area(const Point &a, const Point &b, const Point &c) {
    return std::abs(
        (a.x * (b.y - c.y) + b.x * (c.y - a.y) + c.x * (a.y - b.y)) / (2.0));
  }
  static bool in_triangle(const Point &p, const Triangle &tri) {
    const auto &[a, b, c] = tri;
    double A = triangle_area(a, b, c);
    double A1 = triangle_area(p, b, c);
    double A2 = triangle_area(a, p, c);
    double A3 = triangle_area(a, b, p);
    return std::abs(A - (A1 + A2 + A3)) < 1e-9;
  }
}

;
} // namespace geometry

} // namespace compgeo
