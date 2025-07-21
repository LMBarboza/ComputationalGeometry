#pragma once

#include "../../geometry/point.hpp"
#include "../../geometry/triangle.hpp"
#include <vector>

namespace compgeo {
namespace algorithms {
namespace triangulation {

struct SplittingTag {};
struct IncrementalTag {};

template <typename Tag> struct TriangulationAlgorithm;

template <typename Tag>
inline std::vector<geometry::Triangle>
compute(std::vector<geometry::Point> &points, Tag tag) {
  return TriangulationAlgorithm<Tag>::compute(points, tag);
}

template <typename Tag>
inline std::vector<geometry::Triangle>
compute_delauney(std::vector<geometry::Point> &points, Tag tag) {
  return TriangulationAlgorithm<Tag>::compute_delauney(points, tag);
}
} // namespace triangulation

} // namespace algorithms

} // namespace compgeo
