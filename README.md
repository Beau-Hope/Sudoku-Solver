# Sudoku-Solver
A desktop Sudoku solver and generator implemented in C++ using Qt.
It features a recursive backtracking algorithm for solving puzzles and randomised puzzle generation with difficulty level selection.

# About Sudoku
Sudoku is a logic-based number placement puzzle. the objective is to fill a 9x9 grid so that each row, column, and 3x3 box contains all the integers from 1 to 9 inclusive.

I've always enjoyed logic puzzles like Sudoku. When solving these puzzles on paper, it is easy to make a logical error which can unravel your solution many moves down the track. This project provides a desktop implementation to aid the user to focus on solving strategies while ensuring all inputs are valid.

This application allows the user to enter specific puzzles, generate puzzles, and watch the solver complete puzzles through the visual backtracking algorithm.

# Features
 - Solve any Sudoku puzzle using a recursive backtracking algorithm.
 - Generate puzzles of Easy, Medium, and Hard difficulty.
 - Real-time visualisation of the solver’s progress.
 - Validation of user input to prevent illegal moves.
 - Clear and reset puzzle functionality.

# Solving Algorithm
The solver uses backtracking:
1. Scan the grid for the next empty cell.
2. Attempt to place numbers 1 through 9 in that position.
3. Check if this number placement violates Sudoku rules.
4. If a valid number is placed, move to next empty cell recursively.
5. If no number fits, backtrack to previously filled cell and try the next number.

This continues until a solution is found or no solution exists.

# Puzzle Generation Algorithm
The puzzle generator operates by:
1. Filling the board by randomly placing numbers and ensuring the Sudoku solution is valid.
2. Removing cells to create a puzzle with the desired number of clues for the selected difficulty level, ensuring each removal leaves a valid puzzle.

# Project Structure
Folder Structure:
 - src/ : All source code for the project.
 - sudoku/ : Core logic: board representation, solver, and puzzle generator.
 - gui/ : Qt-based GUI: window, table widget, and buttons.
 - main.cpp : Entry point for the application.

File Structure:
 - Board : Represents the Sudoku grid and enforces rules.
 - Solver : Recursive backtracking solver.
 - PuzzleGenerator : Generates puzzles with a unique solution.
 - SudokuTable : Qt widget displaying the board and handling input.
 - MainWindow : Main GUI window with controls and solver integration.

# Built With
 - C++17
 - Qt 6

# Getting Started
1. Clone the repository: git clone https://github.com/Beau-Hope/Sudoku-Solver.git
2. Open the project in Qt Creator.
3. Configure and build the project.
4. Run the application.

# Usage
 - Click a cell to edit it.
 - Enter numbers 1 - 9 or 0 to clear a cell.
 - Use the Generate button to create a puzzle of selected difficulty.
 - Click Solve to automatically solve the puzzle.
 - Violations (invalid moves) are highlighted in red.
 - Active cell is highlighted in green/pink (if backtracking).
 - Grey cells represent fixed input cells.
 - Warnings/exceptions may pop-up to indicate no solution.

# Future Improvements
 - Detect multiple valid solutions
 - Compare alternative solving algorithms
 - Implement advanced solving techniques