#pragma once

#include "../../geometry/point.hpp"
#include "../../geometry/triangle.hpp"
#include "triangulation.hpp"
#include <algorithm>
#include <tuple>
#include <vector>

namespace compgeo {
namespace algorithms {
namespace triangulation {

template <> struct TriangulationAlgorithm<IncrementalTag> {
  static std::vector<geometry::Triangle>
  compute(std::vector<geometry::Point> &points, IncrementalTag) {
    std::vector<geometry::Triangle> triangles;
    if (points.size() < 3)
      return triangles;

    std::sort(points.begin(), points.end(),
              [](const geometry::Point &a, const geometry::Point &b) {
                return a.x < b.x || (a.x == b.x && a.y < b.y);
              });

    triangles.emplace_back(points[0], points[1], points[2]);
    std::vector<geometry::Point> processed = {points[0], points[1], points[2]};

    for (size_t i = 3; i < points.size(); ++i) {
      const geometry::Point &p = points[i];

      std::vector<geometry::Triangle> new_tris;

      for (const auto &tri : triangles) {
        const geometry::Point &a = std::get<0>(tri);
        const geometry::Point &b = std::get<1>(tri);
        const geometry::Point &c = std::get<2>(tri);

        if (geometry::Triangle::orientation(p, a, b) > 0)
          new_tris.emplace_back(p, a, b);
        if (geometry::Triangle::orientation(p, b, c) > 0)
          new_tris.emplace_back(p, b, c);
        if (geometry::Triangle::orientation(p, c, a) > 0)
          new_tris.emplace_back(p, c, a);
      }

      for (const auto &t : new_tris)
        triangles.push_back(t);

      processed.push_back(p);
    }

    return triangles;
  }

  static std::vector<geometry::Triangle>
  compute_delauney(std::vector<geometry::Triangle> &triangles, IncrementalTag) {
    return triangles;
  }
};
} // namespace triangulation

} // namespace algorithms

} // namespace compgeo
