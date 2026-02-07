#pragma once

#include "Board.h"

class PuzzleGenerator {
public:
    enum class Difficulty {
        Easy,
        Medium,
        Hard
    };

    static Board generate(Difficulty difficulty);

private:
    static bool fillBoard(Board& board);
    static void removeCells(Board& board, Difficulty difficulty);
};
