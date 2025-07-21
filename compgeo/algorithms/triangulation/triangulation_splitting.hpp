#pragma once

#include "../../geometry/point.hpp"
#include "../../geometry/triangle.hpp"
#include "../convex_hull/convex_hull.hpp"
#include "triangulation.hpp"
#include <algorithm>
#include <vector>

namespace compgeo {
namespace algorithms {
namespace triangulation {

template <> struct TriangulationAlgorithm<SplittingTag> {
  static std::vector<geometry::Triangle>
  compute(std::vector<geometry::Point> &points, SplittingTag) {
    if (points.size() < 3)
      return {};

    std::vector<geometry::Point> hull =
        convex_hull::compute(points, convex_hull::GrahamScanTag{});

    std::vector<geometry::Triangle> triangles;
    for (size_t i = 1; i + 1 < hull.size(); ++i) {
      triangles.emplace_back(hull[0], hull[i], hull[i + 1]);
    }

    std::vector<geometry::Point> interior;
    for (const auto &p : points) {
      if (std::find(hull.begin(), hull.end(), p) != hull.end())
        continue;

      int cnt = 0;
      for (size_t i = 0; i < hull.size(); ++i) {
        const auto &a = hull[i];
        const auto &b = hull[(i + 1) % hull.size()];
        if ((a.y > p.y) != (b.y > p.y)) {
          double atX = (b.x - a.x) * (p.y - a.y) / (b.y - a.y + 1e-9) + a.x;
          if (p.x < atX)
            cnt++;
        }
      }
      if (cnt % 2 == 1) {
        interior.push_back(p);
      }
    }

    for (const auto &ip : interior) {
      for (size_t i = 0; i < triangles.size(); ++i) {
        if (geometry::Triangle::in_triangle(ip, triangles[i])) {
          auto [a, b, c] = triangles[i];
          triangles.erase(triangles.begin() + i);
          triangles.emplace_back(a, b, ip);
          triangles.emplace_back(b, c, ip);
          triangles.emplace_back(c, a, ip);
          break;
        }
      }
    }

    return triangles;
  }

  static std::vector<geometry::Triangle>
  compute_delauney(std::vector<geometry::Triangle> &triangles, SplittingTag) {
    return triangles;
  }
};
} // namespace triangulation

} // namespace algorithms

} // namespace compgeo
