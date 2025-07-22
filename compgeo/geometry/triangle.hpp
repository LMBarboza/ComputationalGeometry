#pragma once

#include "point.hpp"
namespace compgeo {
namespace geometry {

struct Triangle {
  Point a, b, c;

  static double triangle_area(const Point &a, const Point &b, const Point &c) {
    return std::abs(
        (a.x * (b.y - c.y) + b.x * (c.y - a.y) + c.x * (a.y - b.y)) / (2.0));
  }
  static double orientation(const Point &a, const Point &b, const Point &c) {
    // > 0 => CCW, < 0 => CW, == 0 => colinear
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
  }
  static bool in_triangle(const Point &p, const Triangle &tri) {
    const Point &a = tri.a;
    const Point &b = tri.b;
    const Point &c = tri.c;

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
