#pragma once

#include <array>

class Board {
public:
    static constexpr int SIZE = 9;
    static constexpr int BOX_SIZE = 3;

    using Grid = std::array<std::array<int, SIZE>, SIZE>;
    using FixedGrid = std::array<std::array<bool, SIZE>, SIZE>;

    //Constructor
    Board();
    explicit Board(const Grid& initialGrid);

    //Access
    int getCell(int row, int col) const;
    void setCell(int row, int col, int value, bool fixed = false);

    //Query
    bool isCellEmpty(int row, int col) const;
    bool isValidMove(int row, int col, int value) const;
    bool isValidBoard();
    bool isSolved() const;
    bool isFixed(int row, int col) const;

    const Grid& getGrid() const;
    void clear();
    void print() const;

private:
    Grid grid{};
    FixedGrid fixed{};

    bool isValidRow(int row, int value) const;
    bool isValidCol(int col, int value) const;
    bool isValidBox(int boxRow, int boxCol, int value) const;
};