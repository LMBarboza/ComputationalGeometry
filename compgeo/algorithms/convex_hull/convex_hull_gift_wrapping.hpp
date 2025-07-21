#pragma once

#include "../../geometry/point.hpp"
#include "convex_hull.hpp"
#include <vector>

namespace compgeo {
namespace algorithms {
namespace convex_hull {

template <> struct ConvexHullAlgorithm<GiftWrappingTag> {
  static std::vector<geometry::Point>
  compute(std::vector<geometry::Point> &points, GiftWrappingTag) {
    std::vector<geometry::Point> hull;
    if (points.size() < 3)
      return points;

    int leftmost = 0;
    for (int i = 1; i < points.size(); ++i) {
      if (points[i].x < points[leftmost].x ||
          (points[i].x == points[leftmost].x &&
           points[i].y < points[leftmost].y)) {
        leftmost = i;
      }
    }

    int p = leftmost;
    do {
      hull.push_back(points[p]);
      int next = (p + 1) % points.size();

      for (int i = 0; i < points.size(); ++i) {
        if (geometry::Point::cross(points[p], points[next], points[i]) < 0) {
          next = i;
        }
      }

      p = next;
    } while (p != leftmost);

    return hull;
  }
}

;
} // namespace convex_hull

} // namespace algorithms

} // namespace compgeo
