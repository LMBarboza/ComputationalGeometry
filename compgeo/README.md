This directory contains C++ implementations of Convex Hull and Triangulation algorithms

A Python script is provided to visualize the results.

## Structure
- **`main.cpp`** – Entry point for generating random points and running both algorithms.
- **`Makefile`** – Used to build the C++ executable.
- **`data/`** – Directory where output files are stored (results of convex hull and triangulation).
- **`plot.py`** – Python script to read the output data and plot the results.

## Running

### Step 1: Build and Run C++ Code
```bash
make
./main.out
````

This generates random points, computes both algorithms, and saves the results to the `data/` directory.

### Step 2: Plot Results

Dependencies are specified in the `pyproject.toml` file.
The Python plotting script can be run either inside a virtual environment or using [uv](https://github.com/astral-sh/uv).

#### Option 1: Using a Virtual Environment

```bash
python plot.py
```

#### Option 2: Using uv

```bash
uv run plot.py
```

---

### Notes

* There are some examples in the `images` directory.
