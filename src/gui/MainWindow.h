#pragma once

#include <QMainWindow>
#include <QPushButton>

#include "SudokuTable.h"
#include "../sudoku/Board.h"
#include "../sudoku/Solver.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);

private slots:
    void startSolver();

private:
    Board board;
    Solver solver;

    SudokuTable* sudokuTable;
    QPushButton* solveButton;

    bool fixedCells[9][9]{};

    void setupUI();
    void readBoardFromUI();
    void updateUI(int row, int col, bool backtracking);
    bool isValidInput();
};
