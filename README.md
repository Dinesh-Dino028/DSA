## DSA — Collection of C++ Data Structures & Algorithms

This repository contains a set of standalone C++ example programs that demonstrate common data structures and algorithms (arrays, stacks, queues, trees, graphs, sorting, dynamic programming, etc.). Each `.cpp` file is typically a small, self-contained demonstration or practice implementation used for learning and competitive programming.

## How to build and run

The workspace is set up for building individual C++ files using `g++` (the included VS Code task uses `C:\msys64\ucrt64\bin\g++.exe`). Build a single file from the editor using the default "C/C++: g++.exe build active file" task or compile from a terminal:

```powershell
g++ -g path\\to\\file.cpp -o path\\to\\file.exe
```

On Windows PowerShell, you can run the produced `.exe` directly. Use the VS Code build task for convenience.

## File index (inferred from workspace)

Below is a quick index of the main source files and their likely purpose (inferred from filenames).

- `Arrays.cpp` — array algorithms and examples
- `BinarySearch.cpp` — binary search examples
- `binarySearchTree.cpp` — binary search tree operations
- `backtracking.cpp` — backtracking problems (permutations, subsets, N-Queens, ...)
- `DisjointSet.cpp` / `disjointSet.cpp` — union-find / DSU examples
- `doubleLinkedList.cpp` — doubly linked list operations
- `DynamicProgramming.cpp` — DP patterns and example problems
- `graph.cpp` — graph algorithms: DFS, BFS, topo sort, SCC/safe nodes, island/area problems
- `GreedyAlgo.cpp` — greedy pattern problems
- `heapDS.cpp` — heap / priority queue examples
- `LinkedList.cpp` / `linkedList.cpp` — singly linked list problems
- `MathProblem.cpp` — math/number-theory problems
- `Matrix.cpp` — matrix manipulation problems
- `queues.cpp` — queue examples
- `Recurssion.cpp` — recursion examples and patterns
- `Revision.cpp` — mixed practice snippets / revision notes
- `SimpleProblems.cpp` — small practice problems
- `slidingWindow.cpp` — sliding window patterns and examples
- `Sorting.cpp` — sorting implementations and benchmarks
- `stack.cpp` — stack problems (next greater, balancing parentheses, span, etc.)
- `stringproblem.cpp` — string algorithms and problems
- `tree.cpp` — binary tree algorithms (height, balance, traversals)
- `TrieDS.cpp` — trie (prefix tree) implementation and uses
- `TwoPointerArray.cpp` — two-pointer pattern examples

Each `.exe` in the folder is likely a compiled output of the corresponding `.cpp` file.

## Complexity quick-reference

Complexity | Meaning | Example / Algorithms | Performance
:---|:---|:---|:---
O(1) | Constant time | Accessing array element | 🔥 Fastest
O(log n) | Logarithmic time | Binary search, heap operations | 🚀 Very fast
O(n) | Linear time | Single pass over array / list | 📈 Medium
O(n log n) | Linearithmic time | Merge sort, quick sort (average) | 🔄 Good for sorting
O(n²) | Quadratic time | Bubble sort, selection sort | 🐌 Slow for large n
O(2ⁿ) | Exponential time | Naive recursion for some problems (Fibonacci) | � Very slow

## Notes & next steps

- I inferred file purposes from filenames. If you'd like, I can open specific `.cpp` files and extract short summaries or function lists to make the index more precise.
- I can also add build scripts or a `Makefile`/`tasks.json` that builds the whole repository or runs a selected set of tests.

---
Updated README: provides a clear project overview, build instructions, and an indexed file list for quicker navigation.