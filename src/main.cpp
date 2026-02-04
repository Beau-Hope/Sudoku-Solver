#include <iostream>
#include "sudoku/Board.h"
#include "sudoku/Solver.h"

int main() {
    Board::Grid puzzle {{
        {{5,3,0,0,7,0,0,0,0}},
        {{6,0,0,1,9,5,0,0,0}},
        {{0,9,8,0,0,0,0,6,0}},
        {{8,0,0,0,6,0,0,0,3}},
        {{4,0,0,8,0,3,0,0,1}},
        {{7,0,0,0,2,0,0,0,6}},
        {{0,6,0,0,0,0,2,8,0}},
        {{0,0,0,4,1,9,0,0,5}},
        {{0,0,0,0,8,0,0,7,9}}
    }};

    Board board(puzzle);
    Solver solver(board);

    std::cout << "Initial board:\n";
    board.print();

    if (solver.solve()) {
        std::cout << "\nSolved board:\n";
        board.print();
    } else {
        std::cout << "No solution exists.\n";
    }

    return 0;
}