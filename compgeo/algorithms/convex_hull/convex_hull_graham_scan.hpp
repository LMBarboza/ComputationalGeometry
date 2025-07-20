#pragma once

#include "../../geometry/point.hpp"
#include "convex_hull.hpp"
#include <vector>

namespace compgeo {
namespace algorithms {
namespace convex_hull {

template <> struct ConvexHullAlgorithm<GrahamScanTag> {
  static std::vector<geometry::Point>
  compute(const std::vector<geometry::Point> &points, GrahamScanTag) {
    return points;
  }
}

;
} // namespace convex_hull

} // namespace algorithms

} // namespace compgeo
