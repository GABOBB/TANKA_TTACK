//
// Created by gbb on 29/10/24.
//

#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <QApplication>
#include <QWidget>
#include <QGridLayout>
#include <QDebug>
#include "CellWidget.h"

class GameBoard : public QWidget {
    Q_OBJECT

public:
    GameBoard(int rows, int cols, QWidget* parent = nullptr)
        : QWidget(parent) {
        QGridLayout* gridLayout = new QGridLayout(this);

        // Crear las casillas y conectarlas a las señales.
        for (int row = 0; row < rows; ++row) {
            for (int col = 0; col < cols; ++col) {
                CellWidget* cell = new CellWidget(row, col);
                connect(cell, &CellWidget::leftClicked,
                        this, &GameBoard::handleLeftClick);
                connect(cell, &CellWidget::rightClicked,
                        this, &GameBoard::handleRightClick);

                gridLayout->addWidget(cell, row, col);
            }
        }
    }

    private slots:
        void handleLeftClick(int row, int col) {
        qDebug() << "Moverse a (" << row << "," << col << ")";
    }

    void handleRightClick(int row, int col) {
        qDebug() << "Disparar a (" << row << "," << col << ")";
    }
};

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    GameBoard board(5, 5);  // Tablero de 5x5, ajusta según necesites.
    board.show();
    return app.exec();
}


#endif //GAMEBOARD_H
