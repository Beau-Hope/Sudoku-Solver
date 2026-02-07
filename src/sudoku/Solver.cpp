#include "Solver.h"
#include <vector>
#include <algorithm>
#include <random>

static std::mt19937& rng() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    return gen;
}

Solver::Solver(Board& board) : board(board) {}

void Solver::setCallback(UpdateCallback cb) {
    callback = cb;
}

void Solver::enableRandomMode(bool enable) {
    randomMode = enable;
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

    std::vector<int> nums{1,2,3,4,5,6,7,8,9};
    if (randomMode) {
        std::shuffle(nums.begin(), nums.end(), rng());
    }
    
    for (int num : nums){
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

