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

    if (points.size() < 3) {
      return points;
    }

    std::vector<geometry::Point> hull;

    for (geometry::Point &p : points) {
      while (hull.size() >= 2 && geometry::Point::cross(hull[hull.size() - 2],
                                                        hull.back(), p) <= 0) {
        hull.pop_back();
      }
      hull.push_back(p);
    }

    int start_hull_size = hull.size();

    for (int i = points.size() - 2; i < points.size(); --i) {
      geometry::Point &p = points[i];
      while (hull.size() > start_hull_size &&
             geometry::Point::cross(hull[hull.size() - 2], hull.back(), p) <=
                 0) {
        hull.pop_back();
      }
      hull.push_back(p);
    }

    hull.pop_back();

    return hull;
  }
};
} // namespace convex_hull

} // namespace algorithms

} // namespace compgeo
