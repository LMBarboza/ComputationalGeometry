from typing import List, Tuple
import matplotlib.pyplot as plt
import seaborn as sns

Point = Tuple[float, float]

DataSet = Tuple[List[Point], List[Point]]

CONXEX_HULL_FILE: str = "data/convex_hull_output.txt"
TRIANGLES_FILE: str = "data/triangulation_output.txt"
CONVEX_ALGO_DICT: dict = {0: "Incremental", 1: "Graham Scan", 2: "Gift Wrapping"}


def parse_triangulation_file(filename):
    sets = []
    with open(filename) as f:
        lines = f.readlines()

    i = 0
    while i < len(lines):
        if lines[i].startswith("SET"):
            set_id = int(lines[i].split()[1])
            i += 1
            assert lines[i].strip() == "POINTS"
            i += 1

            points = []
            while i < len(lines) and not lines[i].startswith("TRIANGLES"):
                x, y = map(float, lines[i].split())
                points.append((x, y))
                i += 1

            i += 1  # skip TRIANGLES
            edges = []
            while i < len(lines) and not lines[i].startswith("SET"):
                x1, y1, x2, y2 = map(float, lines[i].split())
                edges.append(((x1, y1), (x2, y2)))
                i += 1

            sets.append({"id": set_id, "points": points, "edges": edges})
        else:
            i += 1

    return sets


def plot_triangulation(sets) -> None:
    sns.set_theme(style="darkgrid")
    fig, axes = plt.subplots(1, len(sets), figsize=(5 * len(sets), 5))

    if len(sets) == 1:
        axes = [axes]

    for ax, data in zip(axes, sets):
        px, py = zip(*data["points"])
        sns.scatterplot(x=px, y=py, ax=ax, color="blue", s=30)

        for p1, p2 in data["edges"]:
            ax.plot([p1[0], p2[0]], [p1[1], p2[1]], color="red", linewidth=1)

        ax.set_title(f"Splitting")
        ax.axis("equal")

    plt.tight_layout()
    plt.show()


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
    sns.set_theme(style="darkgrid")
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
    point_sets = parse_triangulation_file(TRIANGLES_FILE)
    plot_triangulation(point_sets)


if __name__ == "__main__":
    main()
