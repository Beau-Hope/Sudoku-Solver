#pragma once

#include <QMainWindow>
#include <QPushButton>
#include <QSlider>
#include <QComboBox>

#include "SudokuTable.h"
#include "../sudoku/PuzzleGenerator.h"
#include "../sudoku/Board.h"
#include "../sudoku/Solver.h"

/**
 * Main application window for sudoku solver GUI
 * 
 * Handles user interaction, puzzle generation, and 
 * solving logic
 */

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);

private slots:
    // Start solving the current puzzle
    void startSolver();
    // Clear the board and reset UI state
    void resetPuzzle();
    // Generate a new puzzle based on selected difficulty
    void generatePuzzle();

private:
    // Core sudoku logic
    Board board;
    Solver solver;

    // UI components
    SudokuTable* sudokuTable;
    QPushButton* solveButton;
    QPushButton* resetButton;
    QPushButton* generateBtn;
    QSlider* speedSlider;
    QComboBox* difficultyBox;

    // Solver visualisation delay (ms)
    int solverDelayMs = 30;

    // UI setup and helpers
    void setupUI();
    void readBoardFromUI();
    void updateUI(int row, int col, bool backtracking);
    bool isValidInput();
};
