# Packing Optimization

## Table of Contents
- [Packing Optimization](#packing-optimization)
  - [Table of Contents](#table-of-contents)
  - [Installation](#installation)
  - [Building the Project](#building-the-project)
  - [Running the Application](#running-the-application)
  - [Dataset Format](#dataset-format)
  - [Code Documentation](#code-documentation)
  - [Note on OR-Tools and Protobuf Compatibility](#note-on-or-tools-and-protobuf-compatibility)

---

## Installation

Ensure you have Python and `pip` installed. Install the required Python dependencies:

```bash
pip install -r requirements.txt
```

---

## Building the Project

Build the C++ project using CMake:

```bash
mkdir build
cd build
cmake ..
cmake --build .
```

---

## Running the Application

From the `build` directory, run:

```bash
./packing-optimization
```

The application provides an interactive command-line interface for both interactive and batch use. Follow the prompts to select datasets, run algorithms, and view results.

---

## Dataset Format

Place your CSV files in the `data/` directory. Use the following naming convention:

- `Pallets<X>.csv` — contains the list of available pallets/items
- `TruckAndPallets<X>.csv` — contains the truck capacity and (optionally) the same or additional pallet data

Where `<X>` is a dataset identifier (e.g., `01`, `02`, etc.).

Example:

```
data/
  Pallets01.csv
  TruckAndPallets01.csv
  Pallets02.csv
  TruckAndPallets02.csv
  ...
```

---

## Code Documentation

All main algorithms, data structures, and utilities are documented using Doxygen.

To generate or update the documentation:

1. Run `doxygen Doxyfile` from the project root.
2. Open `docs/html/index.html` in your browser to view the documentation.

The `Doxyfile` is included in the repository for reproducibility. Generated documentation (in `docs/html/` and `docs/latex/`) should not be committed to version control.

---

## Note on OR-Tools and Protobuf Compatibility

If you encounter build errors related to protobuf or OR-Tools, it is recommended to **avoid using a system-wide OR-Tools installation**. This project is configured to fetch and build a compatible version of OR-Tools automatically. Using a system-wide OR-Tools may cause version conflicts, especially if you have multiple versions of protobuf (e.g., from Anaconda or other sources) on your system.

If you need to use a system-wide OR-Tools, ensure that its protobuf version matches your build environment exactly. Otherwise, keep the system-wide search commented out in `CMakeLists.txt` for reliable builds.

---
