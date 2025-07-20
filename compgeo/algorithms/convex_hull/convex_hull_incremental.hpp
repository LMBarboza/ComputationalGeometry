#pragma once

#include "../../geometry/point.hpp"
#include "convex_hull.hpp"
#include <algorithm>
#include <vector>

namespace compgeo {
namespace algorithms {
namespace convex_hull {

template <> struct ConvexHullAlgorithm<IncrementalTag> {
  static std::vector<geometry::Point>
  compute(std::vector<geometry::Point> &points, IncrementalTag) {
    std::sort(points.begin(), points.end());
    if (points.size() < 3)
      return points;

    std::vector<geometry::Point> hull(points.begin(), points.begin() + 3);

    for (size_t i = 3; i < points.size(); ++i) {
      hull.push_back(points[i]);

      bool changed = true;
      while (changed) {
        changed = false;
        for (size_t j = 0; j < hull.size(); ++j) {
          size_t prev = (j == 0) ? hull.size() - 1 : j - 1;
          size_t next = (j + 1) % hull.size();

          if (geometry::Point::cross(hull[prev], hull[j], hull[next]) <= 0) {
            hull.erase(hull.begin() + j);
            changed = true;
            break;
          }
        }
      }
    }

    return hull;
  }
};
} // namespace convex_hull

} // namespace algorithms

} // namespace compgeo
