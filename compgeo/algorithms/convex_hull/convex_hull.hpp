#pragma once

#include "../../geometry/point.hpp"
#include <vector>

namespace compgeo {
namespace algorithms {
namespace convex_hull {

struct GrahamScanTag {};
struct GiftWrappingTag {};
struct IncrementalTag {};
struct DivideAndConquerTag {};

template <typename Tag> struct ConvexHullAlgorithm;

template <typename Tag>
inline std::vector<geometry::Point>
compute(std::vector<geometry::Point> &points, Tag tag) {
  return ConvexHullAlgorithm<Tag>::compute(points, tag);
}
} // namespace convex_hull

} // namespace algorithms

} // namespace compgeo
