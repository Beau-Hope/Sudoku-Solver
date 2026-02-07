#pragma once

#include <QWidget>

class SudokuTable : public QWidget {
    Q_OBJECT

public:
    explicit SudokuTable(QWidget* parent = nullptr);

    void clear();
    void setValue(int r, int c, int v);
    void setFixed(int r, int c, bool f);
    void setInvalid(int r, int c, bool inv);
    void setActiveCell(int r, int c, bool backtracking);
    void setSolved(bool s);

    int value(int r, int c) const;

signals:
    void cellEdited(int row, int col, int value);

protected:
    void paintEvent(QPaintEvent*) override;
    void mousePressEvent(QMouseEvent*) override;
    void keyPressEvent(QKeyEvent*) override;

private:
    QRect cellRect(int r, int c) const;

    int grid[9][9]{};
    bool fixed[9][9]{};
    bool invalid[9][9]{};

    int selectedRow = -1;
    int selectedCol = -1;
    int activeRow = -1;
    int activeCol = -1;

    bool isBacktracking = false;
    bool solved = false;
};
