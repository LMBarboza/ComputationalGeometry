#include "compgeo/algorithms/convex_hull/convex_hull.hpp"
#include "compgeo/compgeo.hpp"
#include <fstream>
#include <random>

using compgeo::geometry::Point;

std::vector<Point> generate_random_points(int n, int seed_offset) {
  std::mt19937 gen(42 + seed_offset);
  std::uniform_real_distribution<> dist(-10, 10);
  std::vector<Point> pts(n);
  for (int i = 0; i < n; ++i)
    pts[i] = {dist(gen), dist(gen)};
  return pts;
}

void write_set(std::ofstream &file, int set_id,
               const std::vector<Point> &points,
               const std::vector<Point> &hull) {
  file << "SET " << set_id << "\n";
  file << "POINTS\n";
  for (const auto &p : points)
    file << p.x << " " << p.y << "\n";

  file << "HULL\n";
  for (const auto &p : hull)
    file << p.x << " " << p.y << "\n";
}

int main(void) {
  std::ofstream file("hull_output.txt");

  auto points = generate_random_points(30, 0);
  auto hull = compgeo::algorithms::convex_hull::compute(
      points, compgeo::algorithms::convex_hull::IncrementalTag{});
  write_set(file, 0, points, hull);

  auto points_1 = generate_random_points(30, 1);
  auto hull_1 = compgeo::algorithms::convex_hull::compute(
      points_1, compgeo::algorithms::convex_hull::GrahamScanTag{});
  write_set(file, 1, points_1, hull_1);

  auto points_2 = generate_random_points(30, 2);
  auto hull_2 = compgeo::algorithms::convex_hull::compute(
      points_2, compgeo::algorithms::convex_hull::GiftWrappingTag{});
  write_set(file, 2, points_2, hull_2);

  return 0;
}
