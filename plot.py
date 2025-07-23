from typing import List, Tuple
import matplotlib.pyplot as plt
import seaborn as sns

Point = Tuple[float, float]

DataSet = Tuple[List[Point], List[Point]]

CONXEX_HULL_FILE: str = "convex_hull_output.txt"
CONVEX_ALGO_DICT: dict = {0: "Incremental", 1: "Graham Scan", 2: "Gift Wrapping"}


def parse_convex_hull_file(filename: str) -> List[DataSet]:
    with open(filename, "r") as f:
        lines = [line.strip() for line in f.readlines()]

    sets: List[DataSet] = []

    i = 0
    while i < len(lines):
        if lines[i].startswith("SET"):
            i += 1
            assert lines[i].strip() == "POINTS"
            i += 1

            points = []
            while i < len(lines) and not lines[i].startswith("HULL"):
                x, y = map(float, lines[i].split())
                points.append((x, y))
                i += 1

            i += 1
            hull = []
            while i < len(lines) and not lines[i].startswith("SET"):
                x, y = map(float, lines[i].split())
                hull.append((x, y))
                i += 1

            sets.append((points, hull))
        else:
            i += 1

    return sets


def plot_convex_hulls(sets_to_plot: List[DataSet]) -> None:

    num_sets = len(sets_to_plot)
    sns.set_theme(style="whitegrid")
    fig, axes = plt.subplots(1, num_sets, figsize=(5 * num_sets, 5), squeeze=False)

    for idx, (points, hull) in enumerate(sets_to_plot):
        ax = axes[0, idx]

        point_x, point_y = zip(*points)
        closed_hull = hull + [hull[0]]
        hull_x, hull_y = zip(*closed_hull)

        sns.scatterplot(x=point_x, y=point_y, ax=ax, color="blue", s=30, label="Points")
        ax.plot(hull_x, hull_y, color="red", linewidth=2, label="Convex Hull")

        ax.set_title(f"{CONVEX_ALGO_DICT[idx]}")
        ax.set_xlabel("X")
        ax.set_ylabel("Y")
        ax.axis("equal")
        ax.legend()

    plt.tight_layout()
    plt.show()


def main() -> None:
    point_sets = parse_convex_hull_file(CONXEX_HULL_FILE)
    plot_convex_hulls(point_sets)


if __name__ == "__main__":
    main()
