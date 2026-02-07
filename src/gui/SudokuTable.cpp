#include "SudokuTable.h"

#include <QPainter>
#include <QMouseEvent>
#include <QKeyEvent>
#include <algorithm>

SudokuTable::SudokuTable(QWidget* parent)
    : QWidget(parent)
{
    setFocusPolicy(Qt::StrongFocus);
    setMinimumSize(minSize, minSize);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}

void SudokuTable::clear() {
    memset(grid, 0, sizeof(grid));
    memset(fixed, 0, sizeof(fixed));
    memset(invalid, 0, sizeof(invalid));

    selectedRow = selectedCol = -1;
    solved = false;
    
    update();
}

void SudokuTable::setValue(int row, int col, int val) {
    grid[row][col] = val;
    update();
}

void SudokuTable::setFixed(int row, int col, bool f) {
    fixed[row][col] = f;
}

void SudokuTable::setInvalid(int row, int col, bool inv) {
    invalid[row][col] = inv;
    update();
}

void SudokuTable::setSolved(bool s) {
    solved = s;
    update();
}

void SudokuTable::setActiveCell(int row, int col, bool backtracking) {
    activeRow = row;
    activeCol = col;
    isBacktracking = backtracking;
    update();
}

int SudokuTable::cellSize() const {
    int size = std::max(std::min(width(), height()), minSize);
    return size / 9;
}

QRect SudokuTable::boardRect() const {
    int size = cellSize() * 9;
    int x = (width() - size) / 2;
    int y = (height() - size) / 2;
    return QRect(x, y, size, size);
}

QRect SudokuTable::cellRect(int row, int col) const {
    QRect board = boardRect();
    int cell = cellSize();
    return QRect(board.left() + col * cell,
                 board.top() + row * cell,
                 cell,
                 cell);
}

void SudokuTable::mousePressEvent(QMouseEvent* e) {
    QRect board = boardRect();
    if (!board.contains(e->pos())) return;

    int cell = cellSize();
    selectedCol = (e->pos().x() - board.left()) / cell;
    selectedRow = (e->pos().y() - board.top()) / cell;

    update();
}

void SudokuTable::keyPressEvent(QKeyEvent* e) {
    if (selectedRow < 0 || fixed[selectedRow][selectedCol]) return;

    int value = 0;
    if (e->key() >= Qt::Key_1 && e->key() <= Qt::Key_9) {
        value = e->key() - Qt::Key_0;
    } else if (e->key() == Qt::Key_Backspace || e->key() == Qt::Key_Delete){
        value = 0;
    } else {
        return;
    }

    emit cellEdited(selectedRow, selectedCol, value);
}

void SudokuTable::paintEvent(QPaintEvent*) {
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);

    QRect board = boardRect();
    int cell = cellSize();

    p.fillRect(rect(), Qt::white);
    if (solved) {
        p.fillRect(board, QColor(220, 255, 220));
    }

    //Draw cells
    for (int row = 0; row < 9; row++) {
        for (int col = 0; col < 9; col++) {
            QRect rect = cellRect(row, col);

            //invalid moves
            if (invalid[row][col]) {
                p.fillRect(rect, QColor(255, 200, 200));
            }
            //selected cell
            else if (row == selectedRow && col == selectedCol) {
                p.fillRect(rect, QColor(220, 235, 255));
            }
            //grey 'fixed' cells
            else if (fixed[row][col]) {
                p.fillRect(rect, QColor(235, 235, 235));
            }

            //solver active cell
            if (row == activeRow && col == activeCol) {
                QColor hl = isBacktracking
                    ? QColor(255, 190, 190)
                    : QColor(190, 255, 190);
                p.fillRect(rect, hl);
            }

            //draw number
            if (grid[row][col] != 0) {
                QFont f;
                f.setBold(fixed[row][col]);
                f.setPointSizeF(cell * 0.55);
                p.setFont(f);
                p.setPen(Qt::black);
                p.drawText(rect, Qt::AlignCenter,
                           QString::number(grid[row][col]));
            }
        }
    }

    //draw grid lines
    for (int i = 0; i <= 9; i++) {
        QPen pen(i % 3 == 0 ? Qt::black : Qt::gray);
        pen.setWidth(i % 3 == 0 ? 3 : 1);
        p.setPen(pen);

        p.drawLine(board.left(), board.top()+i*cell, board.right(), board.top()+i*cell);
        p.drawLine(board.left()+i*cell, board.top(), board.left()+i*cell, board.bottom());
    }
}

int SudokuTable::value(int row, int col) const {
    return grid[row][col];
}
