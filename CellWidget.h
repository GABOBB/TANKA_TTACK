//
// Created by gbb on 29/10/24.
//

#ifndef CELLWIDGET_H
#define CELLWIDGET_H

#include <QWidget>
#include <QMouseEvent>
#include <QDebug>

class CellWidget : public QWidget {
    Q_OBJECT

public:
    CellWidget(int row, int col, QWidget* parent = nullptr)
        : QWidget(parent), row(row), col(col) {
        setStyleSheet("background-color: lightgray; border: 1px solid black;");
    }

    signals:
        void leftClicked(int row, int col);
    void rightClicked(int row, int col);

protected:
    void mousePressEvent(QMouseEvent* event) override {
        if (event->button() == Qt::LeftButton) {
            emit leftClicked(row, col);
        } else if (event->button() == Qt::RightButton) {
            emit rightClicked(row, col);
        }
    }

private:
    int row, col;
};



#endif //CELLWIDGET_H
