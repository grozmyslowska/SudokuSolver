# SudokuSolver
It's a program solving sudoku puzzles implemented with Constrained Satisfaction Problem (CSP) in C++.

# Description

This program is about solving a sudoku puzzle. The goal is to complete the 9 × 9 diagram so that in each row, column, and in each of the nine 3 × 3 squares there is one digit from 1 to 9. The problem is solved by constrained satisfaction problem (CSP). The solution to the CSP problem is any combination of values such that all constraints are satisfied. There may or may not be a solution to the CSP problem, or there may be multiple solutions. The purpose of the search may be to find one arbitrary solution, all solutions, or the optimal solution in terms of any given cost function. In the case of a sudoku puzzle, there should be only one solution.

# Functions

void ConstraintPropagation() – completing the sudoku table with constraints and found solutions 

void FindMinPoss() – finds the field with the fewest possible digits to insert 

int FindResult() – finding the appropriate digit for a given place 

void Initialize() – sudoku table initialization

bool IsSolved() – checks if the given sudoku board has already been solved

void Read() – sudoku reader

void SetConstraint() – assigns possible results to a given field

void SetResult() – enters the result in the appropriate place in the diagram 

void Solve() – solves sudoku by guessing numbers and looking for contradictions 

void Write() – prints out solved Sudoku on output 

# Input format

In one line digits and dots (blank field) of sudoku to solve, from left to right, from up to down.

Example:

......6.91....4.....53.6821..467..5...7...9.....54....37.4.52.6......51..6..2..37
![image](https://user-images.githubusercontent.com/56539204/111923423-6db5db80-8a9f-11eb-88e0-8d025b9f8eec.png)

# Output format

![image](https://user-images.githubusercontent.com/56539204/111923429-79090700-8a9f-11eb-8fbe-c574fb674c5b.png)
