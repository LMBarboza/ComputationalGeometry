import seaborn as sns
import matplotlib.pyplot as plt

sets = []

with open("hull_output.txt") as f:
    lines = f.readlines()

i = 0
while i < len(lines):
    if lines[i].startswith("SET"):
        set_id = int(lines[i].split()[1])
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

sns.set_theme(style="whitegrid")
fig, axes = plt.subplots(1, 3, figsize=(15, 5))

for idx, (points, hull) in enumerate(sets):
    ax = axes[idx]
    px, py = zip(*points)
    hx, hy = zip(*(hull + [hull[0]]))

    sns.scatterplot(x=px, y=py, ax=ax, color="blue", s=30)
    ax.plot(hx, hy, color="red", linewidth=2)
    ax.set_title(f"Conjunto {idx + 1}")
    ax.axis("equal")

plt.tight_layout()
plt.show()
