#pragma once
#include "../../geometry/point.hpp"
#include "convex_hull.hpp"
#include <algorithm>
#include <vector>

namespace compgeo {
namespace algorithms {
namespace convex_hull {

template <> struct ConvexHullAlgorithm<GrahamScanTag> {
  static std::vector<geometry::Point>
  compute(std::vector<geometry::Point> &points, GrahamScanTag) {
    if (points.size() < 3)
      return points;

    int anchor_idx = 0;
    for (int i = 1; i < points.size(); ++i) {
      if (points[i].y < points[anchor_idx].y ||
          (points[i].y == points[anchor_idx].y &&
           points[i].x < points[anchor_idx].x)) {
        anchor_idx = i;
      }
    }
    std::swap(points[0], points[anchor_idx]);
    geometry::Point anchor = points[0];

    std::sort(points.begin() + 1, points.end(),
              [anchor](geometry::Point &a, geometry::Point &b) {
                double c = geometry::Point::cross(anchor, a, b);
                if (c == 0)
                  return geometry::Point::distance(anchor, a) <
                         geometry::Point::distance(anchor, b);
                return c > 0;
              });

    std::vector<geometry::Point> hull;
    hull.push_back(points[0]);
    hull.push_back(points[1]);

    for (int i = 2; i < points.size(); ++i) {
      while (hull.size() >= 2 &&
             geometry::Point::cross(hull[hull.size() - 2],
                                    hull[hull.size() - 1], points[i]) <= 0) {
        hull.pop_back();
      }
      hull.push_back(points[i]);
    }

    return hull;
  }
}

;
} // namespace convex_hull

} // namespace algorithms

} // namespace compgeo
