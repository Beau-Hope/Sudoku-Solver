#pragma once

#include "Board.h"

class Solver {
public:
    explicit Solver(Board& initialBoard);

    bool solve();
private:
    Board& board;

    bool solveRecursive();
    bool findEmptyCell(int& row, int& col) const;

};