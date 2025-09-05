# CPP

This repository contains my journey and practice with C++ programming, including Data Structures and Algorithms (DSA) problems, STL usage, and core C++ concepts. The codebase is organized into several folders based on different phases of my learning.

---

## Folder Structure

### [`Tuts/`](Tuts/)

This folder contains C++ files created while following the [CodeWithHarry](https://www.codewithharry.com/) C++ tutorial series. It covers fundamental C++ concepts, syntax, and beginner exercises.

**Topics Covered:**

- Input/Output operations
- Variables, Data Types, and Operators
- Control Flow (if, switch, loops)
- Functions and Function Overloading
- Arrays, Pointers, and References
- Structures, Unions, and Enums
- OOP Basics (Classes, Objects, Constructors)
- Inline Functions, Default Arguments
- Recursion (Factorial, Fibonacci)
- Miscellaneous exercises

### [`restart/`](restart/)

This folder marks my return to C++ after a break, focusing on revision and deeper understanding. It includes more advanced C++ concepts, STL containers, and OOP exercises.

**Topics Covered:**

- OOP Concepts (Classes, Constructors, Inheritance, Friend Functions)
- Hybrid Inheritance and Ambiguity Resolution
- Reference Variables and Function References
- STL Containers: Vector, List, Set, Map, Priority Queue
- Functors and Custom Comparators
- Practice exercises and revision files

### [`DSA/`](DSA/)

This folder contains implementations of classic DSA problems and algorithms, focusing on efficient solutions and problem-solving techniques.

**Problems & Algorithms Covered:**

- [Aggressive Cows Problem](DSA/aggresive_cows_problem.cpp) (Binary Search on Answer)
- [Book Allocation Problem](DSA/book_allocation_problem.cpp) (Binary Search)
- [Majority Element](DSA/majority_element.cpp) (Moore's Voting Algorithm)
- [Maximum Subarray Sum](DSA/maximum_subarray_sum.cpp) (Kadane's Algorithm)
- [Painters Partition Problem](DSA/painters_partition_problem.cpp) (Binary Search)
- [Pair Sum in Sorted Array](DSA/pair_sum.cpp) (Two Pointers)
- [Rotated Array Search](DSA/rotated_array_search.cpp) (Modified Binary Search)
- [Stack Parenthesis Matching](DSA/stack_parenthesis_matching.cpp) (Custom Stack Implementation)
- [DNF Algorithm](DSA/DNF_algorithm.cpp) (Dutch National Flag Algorithm for 0s, 1s and 2s sorting)

---

## Getting Started

- All code is written in standard C++ and can be compiled using any modern C++ compiler (e.g., g++, clang++).
- No external dependencies are required.
- Each file is self-contained and can be run independently.

---

## How to Compile C++ Files

You can compile any `.cpp` file in this repository using the `g++` compiler. It is recommended to compile output files into a separate `bin/` folder to keep the workspace clean. You can create the `bin/` folder if it does not exist.

### On Linux/macOS

```sh
mkdir -p bin
g++ path/to/your_file.cpp -o bin/your_program
./bin/your_program
```

### On Windows (using MinGW)

```sh
mkdir bin
g++ path\to\your_file.cpp -o bin\your_program.exe
bin\your_program.exe
```

> **Recommendation:**  
> Always compile your executables into the `bin/` directory. This keeps your source folders clean and makes it easy to add `bin/` to `.gitignore` so compiled files are not

## Author

**[Aryan Sisodiya](https://github.com/InfinityxR9)**

---

Feel free to explore, learn, and contribute!
