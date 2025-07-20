#pragma once
#include "point.hpp"
#include <cmath>
#include <vector>

namespace compgeo {
namespace geometry {

template <typename T> struct Polygon {
  std::vector<Point> vertices;

  Polygon() = default;
  explicit Polygon(const std::vector<Point> &verts) : vertices(verts) {}

  double area() const {
    double a = 0;
    size_t n = vertices.size();
    for (size_t i = 0; i < n; ++i) {
      const auto &p = vertices[i];
      const auto &q = vertices[(i + 1) % n];
      a += p.x * q.y - p.y * q.x;
    }
    return a / 2.0;
  }

  bool is_convex() const {
    size_t n = vertices.size();
    if (n < 3)
      return false;

    bool got_positive = false;
    bool got_negative = false;

    for (size_t i = 0; i < n; ++i) {
      const auto &a = vertices[i];
      const auto &b = vertices[(i + 1) % n];
      const auto &c = vertices[(i + 2) % n];

      double cross_prod = Point::cross(b, c, a);
      if (cross_prod > 0)
        got_positive = true;
      else if (cross_prod < 0)
        got_negative = true;

      if (got_positive && got_negative)
        return false;
    }
    return true;
  }

  bool contains(const Point &p) const {
    bool inside = false;
    size_t n = vertices.size();

    for (size_t i = 0, j = n - 1; i < n; j = i++) {
      const auto &pi = vertices[i];
      const auto &pj = vertices[j];

      bool intersect =
          ((pi.y > p.y) != (pj.y > p.y)) &&
          (p.x < (pj.x - pi.x) * (p.y - pi.y) / (pj.y - pi.y) + pi.x);
      if (intersect)
        inside = !inside;
    }
    return inside;
  }
};
} // namespace geometry
} // namespace compgeo
