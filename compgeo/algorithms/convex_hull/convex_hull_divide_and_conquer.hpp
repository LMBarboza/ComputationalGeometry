#pragma once

#include "../../geometry/point.hpp"
#include "convex_hull.hpp"
#include <vector>

namespace compgeo {
namespace algorithms {
namespace convex_hull {

template <> struct ConvexHullAlgorithm<DivideAndConquerTag> {
  static std::vector<geometry::Point>
  compute(const std::vector<geometry::Point> &points, DivideAndConquerTag) {
    return points;
  }
}

;
} // namespace convex_hull

} // namespace algorithms

} // namespace compgeo
