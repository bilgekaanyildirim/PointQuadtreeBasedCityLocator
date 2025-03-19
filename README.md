# Point Quadtree-Based City Locator

This project implements a **Point Quadtree** in C++ to store and query cities based on their 2D coordinates. The program constructs a **spatial data structure**, allowing efficient searches for cities within a specified radius.

## Features
- **Builds a Point Quadtree** dynamically from a list of cities.
- **Searches for cities within a given radius** from a specified point.
- **Efficiently organizes and queries spatial data** using a hierarchical tree structure.
- **Outputs the tree structure** in a formatted manner.
- **Processes queries from an input file** and stores results in an output file.

## Files
- `Quadtree.h` → Header file defining the **Quadtree class** and **City structure**.
- `Quadtree.cpp` → Implementation of the **Quadtree operations** (insertion, searching, printing).
- `source.cpp` → Main file handling **file input/output** and executing **queries**.
