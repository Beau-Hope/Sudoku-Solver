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

void testSetAndGet() {
    Board board;
    board.setCell(0, 0, 5);

    assert(board.getCell(0, 0) == 5);
    assert(!board.isCellEmpty(0, 0));
}

void testRowValidation() {
    Board board;
    board.setCell(0, 0, 9);

    assert(!board.isValidMove(0, 1, 9));
}

void testColumnValidation() {
    Board board;
    board.setCell(0, 0, 8);

    assert(!board.isValidMove(1, 0, 8));
}

void testBoxValidation() {
    Board board;
    board.setCell(0, 0, 7);

    assert(!board.isValidMove(1, 1, 7));
}

void testValidMove() {
    Board board;
    board.setCell(0, 0, 5);

    assert(board.isValidMove(0, 1, 3));
}

void testInvalidBoard() {
    Board::Grid invalidGrid {{
        {{5,5,0,0,0,0,0,0,0}},
        {{0,0,0,0,0,0,0,0,0}},
        {{0,0,0,0,0,0,0,0,0}},
        {{0,0,0,0,0,0,0,0,0}},
        {{0,0,0,0,0,0,0,0,0}},
        {{0,0,0,0,0,0,0,0,0}},
        {{0,0,0,0,0,0,0,0,0}},
        {{0,0,0,0,0,0,0,0,0}},
        {{0,0,0,0,0,0,0,0,0}}
    }};

    bool exceptionThrown = false;

    try {
        Board board(invalidGrid);
    } catch (const std::invalid_argument&) {
        exceptionThrown = true;
    }

    assert(exceptionThrown);
}

void testCompleteBoard() {
    Board::Grid solved {{
        {{5,3,4,6,7,8,9,1,2}},
        {{6,7,2,1,9,5,3,4,8}},
        {{1,9,8,3,4,2,5,6,7}},
        {{8,5,9,7,6,1,4,2,3}},
        {{4,2,6,8,5,3,7,9,1}},
        {{7,1,3,9,2,4,8,5,6}},
        {{9,6,1,5,3,7,2,8,4}},
        {{2,8,7,4,1,9,6,3,5}},
        {{3,4,5,2,8,6,1,7,9}}
    }};

    Board board(solved);

    assert(board.isSolved());
    assert(board.isValidBoard());
}

int main() {
    testEmptyBoard();
    testSetAndGet();
    testRowValidation();
    testColumnValidation();
    testBoxValidation();
    testValidMove();
    testInvalidBoard();
    testCompleteBoard();

    std::cout << "All Board tests passed!\n";
    return 0;
}