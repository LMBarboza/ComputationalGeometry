#pragma once

#include "../../geometry/point.hpp"
#include "../../geometry/triangle.hpp"
#include "../convex_hull/convex_hull.hpp"
#include "triangulation.hpp"
#include <algorithm>
#include <vector>

namespace compgeo {
namespace algorithms {
namespace triangulation {

template <> struct TriangulationAlgorithm<SplittingTag> {
  static std::vector<geometry::Triangle>
  compute(std::vector<geometry::Point> &points, SplittingTag) {
    if (points.size() < 3) {
      return {};
    }

    std::vector<geometry::Point> hull_points =
        convex_hull::compute(points, convex_hull::GrahamScanTag{});

    if (hull_points.size() < 3) {
      return {};
    }

    std::vector<geometry::Triangle> triangles;
    triangles.reserve(points.size() * 2);
    for (int i = 1; i + 1 < hull_points.size(); ++i) {
      triangles.emplace_back(hull_points[0], hull_points[i],
                             hull_points[i + 1]);
    }

    std::sort(points.begin(), points.end());
    std::sort(hull_points.begin(), hull_points.end());

    std::vector<geometry::Point> interior_points;
    std::set_difference(points.begin(), points.end(), hull_points.begin(),
                        hull_points.end(), std::back_inserter(interior_points));

    for (geometry::Point &p : interior_points) {
      std::vector<geometry::Triangle>::iterator in_triang = std::find_if(
          triangles.begin(), triangles.end(), [&p](geometry::Triangle &tri) {
            return geometry::Triangle::in_triangle(p, tri);
          });

      if (in_triang == triangles.end()) {
        continue;
      }

      geometry::Triangle out_triangle = *in_triang;
      geometry::Point v1 = out_triangle.a;
      geometry::Point v2 = out_triangle.b;
      geometry::Point v3 = out_triangle.c;

      *in_triang = geometry::Triangle(v1, v2, p);

      triangles.emplace_back(v2, v3, p);
      triangles.emplace_back(v3, v1, p);
    }

    return triangles;
  }
};
static std::vector<geometry::Triangle> &
compute_delaunay(std::vector<geometry::Triangle> &triangles, SplittingTag) {

  return triangles;
}
} // namespace triangulation
} // namespace algorithms
} // namespace compgeo
