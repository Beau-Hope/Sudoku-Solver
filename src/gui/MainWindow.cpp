#include "MainWindow.h"

#include <QVBoxLayout>
#include <QThread>
#include <QApplication>
#include <QMessageBox>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), solver(board)
{
    setupUI();

    connect(solveButton, &QPushButton::clicked,
            this, &MainWindow::startSolver);
}

void MainWindow::setupUI() {
    setWindowTitle("Sudoku Solver");
    resize(620, 720);

    QWidget* central = new QWidget(this);
    QVBoxLayout* layout = new QVBoxLayout(central);
    layout->setSpacing(15);
    layout->setContentsMargins(20, 20, 20, 20);

    sudokuTable = new SudokuTable(this);

    solveButton = new QPushButton("Solve");
    solveButton->setFixedHeight(50);
    solveButton->setStyleSheet(R"(
        QPushButton {
            background-color: #2c7be5;
            color: white;
            font-size: 18px;
            border-radius: 8px;
        }
        QPushButton:hover { background-color: #1a68d1; }
        QPushButton:pressed { background-color: #155bb5; }
    )");

    layout->addWidget(sudokuTable, 1);
    layout->addWidget(solveButton);

    setCentralWidget(central);

    connect(sudokuTable, &SudokuTable::cellEdited,
        this, [this](int r, int c, int v) {
            board.setCell(r, c, v);
            sudokuTable->setValue(r, c, v);
        });

}

void MainWindow::readBoardFromUI() {
    board.clear();

    for (int r = 0; r < 9; r++) {
        for (int c = 0; c < 9; c++) {
            int val = sudokuTable->value(r, c);
            board.setCell(r, c, val);

            fixedCells[r][c] = (val != 0);
            sudokuTable->setFixed(r, c, fixedCells[r][c]);
        }
    }
}

void MainWindow::updateUI(int row, int col, bool backtracking) {
    for (int r = 0; r < 9; r++) {
        for (int c = 0; c < 9; c++) {
            sudokuTable->setValue(r, c, board.getCell(r, c));
        }
    }

    sudokuTable->setActiveCell(row, col, backtracking);
    QApplication::processEvents();
}

void MainWindow::startSolver() {
    readBoardFromUI();

    if (!isValidInput()) {
        QMessageBox::warning(this,
            "Invalid Sudoku",
            "The puzzle violates Sudoku rules.");
        return;
    }

    solver.setCallback([this](int r, int c, bool backtracking) {
        QThread::msleep(40);
        updateUI(r, c, backtracking);
    });

    sudokuTable->setEnabled(false);
    solver.solve();
    sudokuTable->setEnabled(true);
}


bool MainWindow::isValidInput() {
    for (int r = 0; r < 9; r++) {
        for (int c = 0; c < 9; c++) {
            int v = board.getCell(r, c);
            if (v == 0) continue;

            board.setCell(r, c, 0);
            bool ok = board.isValidMove(r, c, v);
            board.setCell(r, c, v);

            if (!ok)
                return false;
        }
    }
    return true;
}