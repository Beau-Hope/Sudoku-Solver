#pragma once

#include "Board.h"

#include <functional>

/**
 * Backtracking sudoku solver.
 * 
 * Operates on a board instance and reports progress to UI.
 */
class Solver {
public:
    /**
     * Callback signature
     *  
     * row & col : cell modified
     * backtracking : if undoing a move
     */
    using UpdateCallback = std::function<void(int row, int col, bool backtracking)>;

    explicit Solver(Board& initialBoard);

    // Register a callback for UI update
    void setCallback(UpdateCallback cb);

    // Enable random number generation
    void enableRandomMode(bool enable);

    // Start solving current board
    bool solve();

    // Request early stop
    void stop();

private:
    Board& board;
    UpdateCallback callback = nullptr;

    bool stopFlag = false;
    bool randomMode = false;

    // Recursive backtracking solver
    bool solveRecursive();

    // Locate next empty cell (helper)
    bool findEmptyCell(int& row, int& col) const;

};
