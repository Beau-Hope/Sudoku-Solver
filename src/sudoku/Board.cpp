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

bool Board::isValidMove(int row, int col, int value) const {
    if (value == 0) {
        return true; //clearing a cell is valid
    }

    if (!isCellEmpty(row, col)) {
        return false; //shouldn't replace non-empty cells
    }

    return isValidRow(row, value)
        && isValidCol(col, value)
        && isValidBox(row - row % BOX_SIZE,
                      col - col % BOX_SIZE,
                      value);
}

bool Board::isSolved() const {
    for (auto& row : grid){
        for (int value : row){
            if (value == 0){
                return false;
            }
        }
    }
    return true;
}

bool Board::isValidBoard() {
    for (int row = 0; row < SIZE; row++){
        for (int col = 0; col < SIZE; col++){
            int value = grid[row][col];
            if (value != 0) {
                //check if valid
                grid[row][col] = 0;
                bool valid = isValidMove(row, col, value);
                grid[row][col] = value;

                if (!valid){
                    return false;
                }
            }
        }
    }
    return true;
}

const Board::Grid& Board::getGrid() const {
    return grid;
}

void Board::clear() {
    for (auto& row : grid) {
        row.fill(0);
    }
}

//Private
bool Board::isValidRow(int row, int value) const {
    for (int col = 0; col < SIZE; col++){
        if (grid[row][col] == value){
            return false;
        }
    }
    return true;
}

bool Board::isValidCol(int col, int value) const {
    for (int row = 0; row < SIZE; row++){
        if (grid[row][col] == value){
            return false;
        }
    }
    return true;
}

bool Board::isValidBox(int boxRow, int boxCol, int value) const{
    for (int r = 0; r < BOX_SIZE; r++){
        for (int c = 0; c < BOX_SIZE; c++){
            if (grid[boxRow + r][boxCol + c] == value){
                return false;
            }
        }
    }
    return true;
}