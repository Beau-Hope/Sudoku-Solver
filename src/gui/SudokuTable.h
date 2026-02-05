#pragma once
#include <QWidget>

class SudokuTable : public QWidget {
    Q_OBJECT

public:
    explicit SudokuTable(QWidget* parent = nullptr);

    void clear();
    void setValue(int row, int col, int value);
    void setFixed(int row, int col, bool isFixed);
    void setActiveCell(int row, int col, bool backtracking);
    int value(int row, int col) const;

signals:
    void cellEdited(int row, int col, int value);

protected:
    void paintEvent(QPaintEvent*) override;
    void mousePressEvent(QMouseEvent* event) override;
    void keyPressEvent(QKeyEvent* event) override;

private:
    int  grid[9][9]{};
    bool fixed[9][9]{};

    int selectedRow = -1;
    int selectedCol = -1;

    int activeRow = -1;
    int activeCol = -1;
    bool isBacktracking = false;

    QRect cellRect(int row, int col) const;
};
