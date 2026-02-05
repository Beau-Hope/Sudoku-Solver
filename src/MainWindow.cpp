#include "MainWindow.h"
#include <QHeaderView>
#include <QApplication>
#include <QThread>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), solver(board)
{
    QWidget* central = new QWidget(this);
    QVBoxLayout* layout = new QVBoxLayout(central);

    table = new QTableWidget(9, 9, central);
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    table->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    table->setFont(QFont("Arial", 18));

    // Populate cells
    for (int r = 0; r < 9; r++)
        for (int c = 0; c < 9; c++)
            table->setItem(r, c, new QTableWidgetItem(""));

    solveButton = new QPushButton("Solve", central);

    layout->addWidget(table);
    layout->addWidget(solveButton);
    setCentralWidget(central);

    connect(solveButton, &QPushButton::clicked, this, &MainWindow::startSolver);
}

void MainWindow::readTable() {
    for (int r = 0; r < 9; r++) {
        for (int c = 0; c < 9; c++) {
            QTableWidgetItem* item = table->item(r, c);
            if (item && !item->text().isEmpty()) {
                int val = item->text().toInt();
                board.setCell(r, c, (val >= 1 && val <= 9) ? val : 0);
            } else {
                board.setCell(r, c, 0);
            }
        }
    }
}

// Update GUI with highlight
void MainWindow::updateTable(int currentRow, int currentCol, bool backtracking) {
    for (int r = 0; r < 9; r++) {
        for (int c = 0; c < 9; c++) {
            int val = board.getCell(r, c);
            table->item(r, c)->setText(val == 0 ? "" : QString::number(val));

            // Reset background
            table->item(r, c)->setBackground(Qt::white);
        }
    }

    // Highlight curr cell
    if (currentRow >= 0 && currentCol >= 0) {
        QColor color = backtracking ? QColor(255, 200, 200) : QColor(200, 255, 200);
        table->item(currentRow, currentCol)->setBackground(color);
    }

    QApplication::processEvents(); // refresh
}

// Start solver
void MainWindow::startSolver() {
    readTable();

    // Provide a callback for the solver to update GUI
    solver.setCallback([this](int row, int col, bool backtrack) {
        QThread::msleep(50); // slow animation
        updateTable(row, col, backtrack);
    });

    solver.solve(); // blocking call; animation happens via callback
}
