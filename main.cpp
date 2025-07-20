#include "compgeo/compgeo.hpp"

int main(void) {

  std::vector<compgeo::geometry::Point> points = {
      {0, 0}, {1, 1}, {2, 0}, {1, -1}, {1, 0}};

  auto hull = compgeo::algorithms::convex_hull::compute(
      points, compgeo::algorithms::convex_hull::GrahamScanTag{});

  return 0;
}
