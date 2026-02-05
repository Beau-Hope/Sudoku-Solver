#pragma once

#include <QMainWindow>
#include <QTableWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QTimer>
#include "sudoku/Board.h"
#include "sudoku/Solver.h"

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget* parent = nullptr);

private slots:
    void startSolver();

private:
    Board board;
    Solver solver;

    QTableWidget* table;
    QPushButton* solveButton;

    void updateTable(int currentRow = -1, int currentCol = -1, bool backtracking = false);
    void readTable();
};
