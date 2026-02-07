#pragma once

#include <array>

/**
 * Represents a 9x9 sudoku board.
 * 
 * Stores cell values, tracks fixed cells, and provides
 * validation tools for the solver and UI.
 */
class Board {
public:
    static constexpr int SIZE = 9;
    static constexpr int BOX_SIZE = 3;

    using Grid = std::array<std::array<int, SIZE>, SIZE>;
    using FixedGrid = std::array<std::array<bool, SIZE>, SIZE>;

    // Create an empty board
    Board();
    // Create a board from an initial grid
    // Throws std::invalid_argument if the grid violates rules
    explicit Board(const Grid& initialGrid);

    // Accessors
    int getCell(int row, int col) const;
    bool isFixed(int row, int col) const;

    // Mutators
    void setCell(int row, int col, int value, bool fixed = false);

    //Queries
    bool isCellEmpty(int row, int col) const;
    bool isValidMove(int row, int col, int value) const;
    bool isValidBoard();
    bool isSolved() const;

    // Get full grid
    const Grid& getGrid() const;

    // Clear all values and fixed flags
    void clear();

    // Print board to stdout (debugging/early testing)
    void print() const;

private:
    Grid grid{};
    FixedGrid fixed{};

    bool isValidRow(int row, int value) const;
    bool isValidCol(int col, int value) const;
    bool isValidBox(int boxRow, int boxCol, int value) const;
};
