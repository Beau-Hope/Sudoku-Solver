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

void SudokuTable::setValue(int r, int c, int v) {
    grid[r][c] = v;
    update();
}

void SudokuTable::setFixed(int r, int c, bool f) {
    fixed[r][c] = f;
}

void SudokuTable::setInvalid(int r, int c, bool inv) {
    invalid[r][c] = inv;
    update();
}

void SudokuTable::setSolved(bool s) {
    solved = s;
    update();
}

void SudokuTable::setActiveCell(int r, int c, bool backtracking) {
    activeRow = r;
    activeCol = c;
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

QRect SudokuTable::cellRect(int r, int c) const {
    QRect board = boardRect();
    int cell = cellSize();
    return QRect(board.left() + c * cell,
                 board.top() + r * cell,
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
    if (e->key() >= Qt::Key_1 && e->key() <= Qt::Key_9)
        value = e->key() - Qt::Key_0;
    else if (e->key() == Qt::Key_Backspace || e->key() == Qt::Key_Delete)
        value = 0;
    else return;

    emit cellEdited(selectedRow, selectedCol, value);
}

void SudokuTable::paintEvent(QPaintEvent*) {
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);

    QRect board = boardRect();
    int cell = cellSize();

    p.fillRect(rect(), Qt::white);
    if (solved) p.fillRect(board, QColor(220, 255, 220));

    for (int r = 0; r < 9; r++) {
        for (int c = 0; c < 9; c++) {
            QRect rect = cellRect(r, c);

            //invalid moves
            if (invalid[r][c]) {
                p.fillRect(rect, QColor(255, 200, 200));
            }
            //selected cell
            else if (r == selectedRow && c == selectedCol) {
                p.fillRect(rect, QColor(220, 235, 255));
            }
            //grey 'fixed' cells
            else if (fixed[r][c]) {
                p.fillRect(rect, QColor(235, 235, 235));
            }

            //active cell
            if (r == activeRow && c == activeCol) {
                QColor hl = isBacktracking
                    ? QColor(255, 190, 190)
                    : QColor(190, 255, 190);
                p.fillRect(rect, hl);
            }

            //draw no.
            if (grid[r][c] != 0) {
                QFont f;
                f.setBold(fixed[r][c]);
                f.setPointSizeF(cell * 0.55);
                p.setFont(f);
                p.setPen(Qt::black);
                p.drawText(rect, Qt::AlignCenter,
                           QString::number(grid[r][c]));
            }
        }
    }

    //grid
    for (int i = 0; i <= 9; i++) {
        QPen pen(i % 3 == 0 ? Qt::black : Qt::gray);
        pen.setWidth(i % 3 == 0 ? 3 : 1);
        p.setPen(pen);

        p.drawLine(board.left(), board.top()+i*cell, board.right(), board.top()+i*cell);
        p.drawLine(board.left()+i*cell, board.top(), board.left()+i*cell, board.bottom());
    }
}

int SudokuTable::value(int r, int c) const {
    return grid[r][c];
}
