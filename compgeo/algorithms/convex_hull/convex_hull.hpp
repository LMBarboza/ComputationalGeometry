#include "../../geometry/point.hpp"
#include "../../geometry/polygon.hpp"

namespace compgeo {
namespace algorithms {
namespace convex_hull {

template <typename T> struct ConvexHull {

  virtual ~ConvexHull() = default;
  virtual compgeo::geometry::Polygon<T>
  compute(const std::vector<compgeo::geometry::Point<T>> &points) const = 0;
};

} // namespace convex_hull
} // namespace algorithms
} // namespace compgeo
