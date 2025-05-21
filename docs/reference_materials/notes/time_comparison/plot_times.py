import matplotlib
import matplotlib.pyplot as plt
import pandas as pd
from matplotlib.lines import Line2D

# Read the CSV file
csv_path = "times.csv"
df = pd.read_csv(csv_path, skipinitialspace=True)
df.columns = [c.strip() for c in df.columns]

# Convert columns to correct types
df["Flag"] = pd.to_numeric(df["Flag"], errors="coerce").fillna(0).astype(int)
df["Time (μs)"] = pd.to_numeric(df["Time (μs)"], errors="coerce")
df["Dataset"] = pd.to_numeric(df["Dataset"], errors="coerce")

algorithms = df["Algorithm"].unique()
algorithms.sort()

# Assign a color and marker for each algorithm
cmap = matplotlib.colormaps["tab10"]
markers = ["o", "s", "D", "^", "v", "P", "X", "*", "h", "8", "p", "<", ">"]
color_map = {alg: cmap(i % 10) for i, alg in enumerate(algorithms)}
marker_map = {alg: markers[i % len(markers)] for i, alg in enumerate(algorithms)}

plt.figure(figsize=(16, 8))
plt.yscale("log")

# Find the minimum positive time for unfinished marker placement
min_positive = df[df["Time (μs)"] > 0]["Time (μs)"].min()
unfinished_y = min_positive / 10 if min_positive > 0 else 1e-1

# For legend: keep track of which symbols have been added
legend_handles = []

for alg in algorithms:
    sub = df[df["Algorithm"] == alg].copy()
    x = sub["Dataset"]
    y = sub["Time (μs)"]
    flag = sub["Flag"]
    marker = marker_map[alg]
    color = color_map[alg]

    # Points where time == -1 (unfinished)
    unfinished = y == -1
    # Points where flag == 1 and time != -1 (suspicious)
    suspicious = (flag == 1) & (y != -1)
    # Normal points
    normal = (flag == 0) & (y != -1)

    # For line: replace unfinished y with unfinished_y
    y_line = y.astype(float).copy()
    y_line[unfinished] = unfinished_y
    # Plot line through all points (including unfinished)
    plt.plot(x, y_line, "-", color=color, alpha=0.3, zorder=1)

    # Plot normal points
    if normal.any():
        h = plt.scatter(
            x[normal], y[normal], label=alg, color=color, marker=marker, s=60, zorder=2
        )
        legend_handles.append(h)
    # Plot suspicious points with custom markers for Greedy and BB
    if suspicious.any():
        if alg == "Greedy":
            plt.scatter(
                x[suspicious],
                y[suspicious],
                color=color,
                marker="P",  # plus filled marker for Greedy
                edgecolor="black",
                s=100,
                label=None,
                zorder=3,
            )
        elif alg == "BB":
            plt.scatter(
                x[suspicious],
                y[suspicious],
                color=color,
                marker="v",  # triangle down for BB
                edgecolor="black",
                s=100,
                label=None,
                zorder=3,
            )
        else:
            plt.scatter(
                x[suspicious],
                y[suspicious],
                color="gray",
                marker=marker,
                edgecolor="black",
                s=80,
                label=None,
                zorder=3,
            )
    # Plot unfinished at y=unfinished_y with faded symbol and red 'x' on top
    if unfinished.any():
        plt.scatter(
            x[unfinished],
            [unfinished_y] * unfinished.sum(),
            color=color,
            marker=marker,
            s=60,
            alpha=0.3,
            label=None,
            zorder=4,
        )
        plt.scatter(
            x[unfinished],
            [unfinished_y] * unfinished.sum(),
            color="red",
            marker="x",
            s=100,
            label=None,
            zorder=5,
        )

# Custom legend for suspicious and unfinished
custom_legend = [
    Line2D(
        [0],
        [0],
        marker="x",
        color="w",
        label="Unfinished",
        markerfacecolor="red",
        markeredgecolor="red",
        markersize=12,
        linestyle="None",
    ),
    Line2D(
        [0],
        [0],
        marker="P",
        color="w",
        label="Greedy: Not optimal but close",
        markerfacecolor=color_map.get("Greedy", "gray"),
        markeredgecolor="black",
        markersize=12,
        linestyle="None",
    ),
    Line2D(
        [0],
        [0],
        marker="v",
        color="w",
        label="BB: Changed sorting style",
        markerfacecolor=color_map.get("BB", "gray"),
        markeredgecolor="black",
        markersize=12,
        linestyle="None",
    ),
]

# Add algorithm marker legend
for alg in algorithms:
    custom_legend.append(
        Line2D(
            [0],
            [0],
            marker=marker_map[alg],
            color="w",
            label=alg,
            markerfacecolor=color_map[alg],
            markeredgecolor="black",
            markersize=10,
            linestyle="None",
        )
    )

plt.xlabel("Dataset")
plt.ylabel("Time (μs) [log scale]")
plt.title("Algorithm Timing Comparison (log scale)")
plt.legend(
    handles=custom_legend, bbox_to_anchor=(1.01, 1), loc="upper left", borderaxespad=0.0
)
plt.grid(True, linestyle="--", alpha=0.5, which="both")
plt.tight_layout()
plt.savefig("times_plot.png", dpi=300)
plt.close()
print("Plot saved as times_plot.png")
