#pragma once

#include <QWidget>

/**
 * Custom widget for displaying/interacting with the sudoku grid.
 * 
 * Handles rendering, input, cell highlighting and visual feedback.
 */
class SudokuTable : public QWidget {
    Q_OBJECT

public:
    explicit SudokuTable(QWidget* parent = nullptr);

    // Reset board state and clear all values
    void clear();
    // Set a cell value (0 clears the cell)
    void setValue(int r, int c, int v);
    // Mark a cell as fixed (non-editable)
    void setFixed(int r, int c, bool f);
    // Mark a cell as invalid (rule violation)
    void setInvalid(int r, int c, bool inv);
    // Highlight the currently active solver cell
    void setActiveCell(int r, int c, bool backtracking);
    // Set solved visual state
    void setSolved(bool s);
    // Get value stored in a cell
    int value(int r, int c) const;

signals:
    // Emitted when the user edits a cell via keyboard input
    void cellEdited(int row, int col, int value);

protected:
    void paintEvent(QPaintEvent*) override;
    void mousePressEvent(QMouseEvent*) override;
    void keyPressEvent(QKeyEvent*) override;

private:
// Geometry helpers
    QRect cellRect(int r, int c) const;
    int cellSize() const;
    QRect boardRect() const;
    
    const int minSize = 480; // Minimum board starting size

    // Board state
    int grid[9][9]{}; // cell values
    bool fixed[9][9]{}; // initial cells
    bool invalid[9][9]{}; // invalid input moves

    // Selection & solver visualisation
    int selectedRow = -1;
    int selectedCol = -1;
    int activeRow = -1;
    int activeCol = -1;

    bool isBacktracking = false;
    bool solved = false;
};
