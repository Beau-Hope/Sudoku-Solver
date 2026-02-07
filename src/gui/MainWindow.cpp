#include "MainWindow.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QThread>
#include <QApplication>
#include <QMessageBox>
#include <QLabel>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), solver(board)
{
    setupUI();

    connect(solveButton, &QPushButton::clicked,
            this, &MainWindow::startSolver);

    connect(resetButton, &QPushButton::clicked,
            this, &MainWindow::resetPuzzle);

    connect(generateBtn, &QPushButton::clicked,
            this, &MainWindow::generatePuzzle);
}

void MainWindow::setupUI() {
    setWindowTitle("Sudoku Solver");
    resize(620, 720);

    QWidget* central = new QWidget(this);
    QVBoxLayout* layout = new QVBoxLayout(central);
    layout->setSpacing(15);
    layout->setContentsMargins(20, 20, 20, 20);

    sudokuTable = new SudokuTable(this);
    sudokuTable->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

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

    generateBtn = new QPushButton("Generate");
    generateBtn->setFixedHeight(50);
    generateBtn->setStyleSheet(R"(
    QPushButton {
        background-color: #4caf50;
        color: white;
        font-size: 18px;
        border-radius: 8px;
    }
    QPushButton:hover { background-color: #43a047; }
    QPushButton:pressed { background-color: #388e3c; }
    )");

    difficultyBox = new QComboBox;
    difficultyBox->addItems({"Easy","Medium","Hard"});

    layout->addLayout(boardLayout, 1);
    layout->addWidget(speedLabel);
    layout->addWidget(speedSlider);
    layout->addWidget(solveButton);
    layout->addWidget(resetButton);
    layout->addWidget(difficultyBox);
    layout->addWidget(generateBtn);

    setCentralWidget(central);
    
    // Handle cell edits from the sudoku grid
    connect(sudokuTable, &SudokuTable::cellEdited,
        this, [this](int row, int col, int value) {

            sudokuTable->setValue(row, col, value);

            sudokuTable->setInvalid(row, col, false);

            // Clear cell
            if (value == 0) {
                board.setCell(row, col, 0);
                return;
            }

            board.setCell(row, col, 0);

            if (board.isValidMove(row, col, value)) {
                board.setCell(row, col, value);
            } else {
                sudokuTable->setInvalid(row, col, true);
            }
        }
    );
}

void MainWindow::readBoardFromUI() {
    board.clear();

    for (int row = 0; row < 9; row++) {
        for (int col = 0; col < 9; col++) {
            int val = sudokuTable->value(row, col);
            board.setCell(row, col, val);
            sudokuTable->setFixed(row, col, val != 0);
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
    } else {
        QMessageBox::critical(this, "Unsolvable Puzzle",
                              "The puzzle cannot be solved. "
                              "Please try generating a different puzzle.");
    }

    sudokuTable->setEnabled(true);
}

bool MainWindow::isValidInput() {
    for (int row = 0; row < 9; row++) {
        for (int col = 0; col < 9; col++) {
            int val = board.getCell(row, col);
            if (val == 0) continue;

            board.setCell(row, col, 0);
            bool ok = board.isValidMove(row, col, val);
            board.setCell(row, col, val);

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

void MainWindow::generatePuzzle() {
    board.clear();
    sudokuTable->clear();

    auto diff = static_cast<PuzzleGenerator::Difficulty>(
        difficultyBox->currentIndex());

    Board puzzle = PuzzleGenerator::generate(diff);

    for (int row = 0; row < 9; row++) {
        for (int col = 0; col < 9; col++) {
            int v = puzzle.getCell(row, col);
            if (v) {
                board.setCell(row, col, v, true);
                sudokuTable->setValue(row, col, v);
                sudokuTable->setFixed(row, col, true);
            }
        }
    }
}
