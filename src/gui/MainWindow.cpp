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

    connect(resetButton, &QPushButton::clicked,
            this, &MainWindow::resetPuzzle);
}

void MainWindow::setupUI() {
    setWindowTitle("Sudoku Solver");
    resize(620, 720);

    QWidget* central = new QWidget(this);
    QVBoxLayout* layout = new QVBoxLayout(central);
    layout->setSpacing(15);
    layout->setContentsMargins(20, 20, 20, 20);

    sudokuTable = new SudokuTable(this);
    sudokuTable->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    // Center board
    QHBoxLayout* boardLayout = new QHBoxLayout();
    boardLayout->addStretch();
    boardLayout->addWidget(sudokuTable);
    boardLayout->addStretch();

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

    QLabel* speedLabel = new QLabel("Solver speed");
    speedSlider = new QSlider(Qt::Horizontal);
    speedSlider->setRange(0, 100);
    speedSlider->setValue(30);

    connect(speedSlider, &QSlider::valueChanged, this,
        [this](int v) { solverDelayMs = 100 - v; });

    layout->addLayout(boardLayout, 1);
    layout->addWidget(speedLabel);
    layout->addWidget(speedSlider);
    layout->addWidget(solveButton);
    layout->addWidget(resetButton);

    setCentralWidget(central);

    connect(sudokuTable, &SudokuTable::cellEdited,
        this, [this](int r, int c, int v) {

            sudokuTable->setValue(r, c, v);

            sudokuTable->setInvalid(r, c, false);

            if (v == 0) {
                board.setCell(r, c, 0);
                return;
            }

            board.setCell(r, c, 0);

            if (board.isValidMove(r, c, v)) {
                board.setCell(r, c, v);
            } else {
                sudokuTable->setInvalid(r, c, true);
            }
        }
    );
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
        QMessageBox::warning(this, "Invalid Sudoku",
                             "The puzzle violates Sudoku rules.");
        return;
    }

    sudokuTable->setSolved(false);
    sudokuTable->setEnabled(false);

    solver.setCallback([this](int r, int c, bool backtracking) {
        QThread::msleep(solverDelayMs);
        updateUI(r, c, backtracking);
    });

    if (solver.solve()) {
        sudokuTable->setSolved(true);
    }

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

            if (!ok) return false;
        }
    }
    return true;
}

void MainWindow::resetPuzzle() {
    solver.stop();
    board.clear();
    sudokuTable->clear();
    sudokuTable->setSolved(false);
    sudokuTable->setEnabled(true);
}
