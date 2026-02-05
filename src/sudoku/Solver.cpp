#include "Solver.h"

Solver::Solver(Board& board) : board(board) {}

void Solver::setCallback(UpdateCallback cb) {
    callback = cb;
}

bool Solver::solve(){
    stopFlag = false;
    return solveRecursive();
}

bool Solver::solveRecursive(){
    if (stopFlag) return false;
    int row, col;

    if (!findEmptyCell(row, col)){
        return true; //no empty cells = solved
    }
    
    for (int num = 1; num <= 9; num++){
        if (stopFlag) return false;

        if (board.isValidMove(row, col, num)){
            board.setCell(row, col, num);

            if (callback && !stopFlag) callback(row, col, false);

            if (solveRecursive()){
                return true;
            }

            board.setCell(row, col, 0); //Backtrack call
            
            if (callback && !stopFlag) callback(row, col, true);
        }
    }

    return false; //Trigger backtrack
}

bool Solver::findEmptyCell(int& row, int& col) const {
    for (row = 0; row < Board::SIZE; row++){
        for (col = 0; col < Board::SIZE; col++){
            if (board.isCellEmpty(row, col)){
                return true;
            }
        }
    }
    return false;
}

