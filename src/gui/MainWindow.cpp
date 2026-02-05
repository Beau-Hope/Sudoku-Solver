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

    resetButton = new QPushButton("Reset");
    resetButton->setFixedHeight(50);
    resetButton->setStyleSheet(R"(
        QPushButton {
            background-color: #f05454;
            color: white;
            font-size: 18px;
            border-radius: 8px;
        }
        QPushButton:hover { background-color: #d94343; }
        QPushButton:pressed { background-color: #c03636; }
    )");

    layout->addWidget(sudokuTable, 1);
    layout->addWidget(solveButton);
    layout->addWidget(resetButton);

    setCentralWidget(central);

    connect(sudokuTable, &SudokuTable::cellEdited,
        this, [this](int r, int c, int v) {
            board.setCell(r, c, v);
            sudokuTable->setValue(r, c, v);
        }
    );

    connect(resetButton, &QPushButton::clicked,
        this, &MainWindow::resetPuzzle);
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
    sudokuTable->setValue(row, col, board.getCell(row, col));

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
        QThread::msleep(30);
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

void MainWindow::resetPuzzle() {
    solver.stop();
    board.clear();
    sudokuTable->clear();

    for (int r = 0; r < 9; r++){
        for (int c = 0; c < 9; c++) {
            fixedCells[r][c] = false;
        }
    }

    
    sudokuTable->setActiveCell(-1, -1, false);
    sudokuTable->setEnabled(true);
}