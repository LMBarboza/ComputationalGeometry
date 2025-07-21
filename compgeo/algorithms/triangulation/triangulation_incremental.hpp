#pragma once

#include "../../geometry/point.hpp"
#include "../../geometry/triangle.hpp"
#include "triangulation.hpp"
#include <algorithm>
#include <vector>

namespace compgeo {
namespace algorithms {
namespace triangulation {

template <> struct TriangulationAlgorithm<IncrementalTag> {
  static std::vector<geometry::Triangle>
  compute(std::vector<geometry::Point> &points, IncrementalTag) {
    return;
  }

  static std::vector<geometry::Triangle>
  compute_delauney(std::vector<geometry::Triangle> &triangles, IncrementalTag) {
    return;
  }
};
} // namespace triangulation

} // namespace algorithms

} // namespace compgeo
