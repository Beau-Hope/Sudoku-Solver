#pragma once

#include "Board.h"
#include <functional>

class Solver {
public:
    using UpdateCallback = std::function<void(int row, int col, bool backtracking)>;
    explicit Solver(Board& initialBoard);

    void setCallback(UpdateCallback cb);
    void enableRandomMode(bool enable);

    bool solve();
    void stop() { stopFlag = true; }
private:
    Board& board;
    UpdateCallback callback = nullptr;

    bool stopFlag = false;
    bool randomMode = false;

    bool solveRecursive();
    bool findEmptyCell(int& row, int& col) const;

};