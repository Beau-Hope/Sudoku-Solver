#pragma once

#include <array>

class Board {
public:
    static constexpr int SIZE = 9;
    static constexpr int BOX_SIZE = 3;

    using Grid = std::array<std::array<int, SIZE>, SIZE>;

    //Constructor
    Board();
    explicit Board(const Grid& initialGrid);

    //Access
    int getCell(int row, int col) const;
    void setCell(int row, int col, int value);

    //Query
    bool isCellEmpty(int row, int col) const;
    bool isValidMove(int row, int col, int value) const;
    bool isValidBoard() const;
    bool isSolved() const;

    const Grid& getGrid() const;
    void clear();

private:
    Grid grid;

    bool isValidRow(int row, int value) const;
    bool isValidCol(int col, int value) const;
    bool isValidBox(int boxRow, int boxCol, int value) const;
};