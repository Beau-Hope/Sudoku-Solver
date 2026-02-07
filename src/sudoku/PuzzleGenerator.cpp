#include "PuzzleGenerator.h"
#include "Solver.h"

#include <vector>
#include <algorithm>
#include <random>

static std::mt19937& rng() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    return gen;
}

bool PuzzleGenerator::fillBoard(Board& board) {
    Solver solver(board);
    solver.enableRandomMode(true);
    return solver.solve();
}

Board PuzzleGenerator::generate(Difficulty difficulty) {
    Board board;
    fillBoard(board);
    removeCells(board, difficulty);
    return board;
}

void PuzzleGenerator::removeCells(Board& board, Difficulty difficulty) {
    int clues;

    switch (difficulty) {
        case Difficulty::Easy: clues = 38; break;
        case Difficulty::Medium: clues = 32; break;
        case Difficulty::Hard: clues = 26; break;
    }

    std::vector<std::pair<int,int>> cells;
    for (int r = 0; r < 9; r++) {
        for (int c = 0; c < 9; c++) {
            cells.emplace_back(r, c);
        }
    }

    std::shuffle(cells.begin(), cells.end(), rng());

    int toRemove = 81 - clues;

    for (auto& [r, c] : cells) {
        if (toRemove == 0) {
            break;
        }

        int backup = board.getCell(r, c);
        board.setCell(r, c, 0);

        Board copy = board;
        Solver solver(copy);
        solver.enableRandomMode(false);

        if (!solver.solve()) {
            board.setCell(r, c, backup); // revert
        } else {
            toRemove--;
        }
    }
}
