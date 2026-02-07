#pragma once

#include "Board.h"

/**
 * Generates valid sudoku puzzles of varying difficulties.
 * First creates a solved board, then removes numbers to ensure the puzzle remains solvable.
*/
class PuzzleGenerator {
public:
    enum class Difficulty {
        Easy,
        Medium,
        Hard
    };

    /**
     * Generate a sudoku puzzle
     * Param: desired difficulty level
     * Return: partially filled board
     */
    static Board generate(Difficulty difficulty);

private:
    /** 
     * Fill a solved sudoku board
     * Param: board to fill
     * Return: true if solution was generated
    */
    static bool fillBoard(Board& board);

    /**
     * Remove cells from the board based on difficulty
     * Param: solved board to modify
     * Param: desired difficulty level
     */
    static void removeCells(Board& board, Difficulty difficulty);
};
