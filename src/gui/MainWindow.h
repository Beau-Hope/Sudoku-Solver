#pragma once

#include <QMainWindow>
#include <QPushButton>
#include <QSlider>
#include <QLabel>
#include <QComboBox>

#include "SudokuTable.h"
#include "PuzzleGenerator.h"
#include "../sudoku/Board.h"
#include "../sudoku/Solver.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);

private slots:
    void startSolver();
    void resetPuzzle();
    void generatePuzzle();

private:
    Board board;
    Solver solver;

    SudokuTable* sudokuTable;
    QPushButton* solveButton;
    QPushButton* resetButton;
    QSlider* speedSlider;
    QPushButton* generateBtn;
    QComboBox* difficultyBox;

    bool fixedCells[9][9]{};
    int solverDelayMs = 30;

    void setupUI();
    void readBoardFromUI();
    void updateUI(int row, int col, bool backtracking);
    bool isValidInput();
};
