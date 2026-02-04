#include "sudoku/Board.h"
#include <iostream>
#include <cassert>

void testEmptyBoard() {
    Board board;

    for (int r = 0; r < Board::SIZE; r++){
        for (int c = 0; c < Board::SIZE; c++){
            assert(board.isCellEmpty(r,c));
        }
    }

    assert(board.isValidBoard());
}


int main() {
    testEmptyBoard();

    std::cout << "All Board tests passed!\n";
    return 0;
}