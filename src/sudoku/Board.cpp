#include "Board.h"
#include <stdexcept>

//Constructor
Board::Board() {
    clear();
}

Board::Board(const Grid& initialGrid){
    grid = initialGrid;
    if (!isValidBoard()) {
        throw std::invalid_argument("Initial board is invalid");
    }
}

//Public
int Board::getCell(int row, int col) const {
    return grid[row][col];
}

void Board::setCell(int row, int col, int value) {
    if (value < 0 || value > 9) {
        throw std::invalid_argument("Value must be between 0 and 9");
    }
    grid[row][col] = value;
}

bool Board::isCellEmpty(int row, int col) const {
    return grid[row][col] == 0;
}

bool Board::isValidMove(int row, int col, int value) const {}

bool Board::isSolved() const {}

bool Board::isValidBoard() const {}

const Board::Grid& Board::getGrid() const {
    return grid;
}

void Board::clear() {
    for (auto& row : grid) {
        row.fill(0);
    }
}

//Private