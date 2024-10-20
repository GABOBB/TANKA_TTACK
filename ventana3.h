//
// Created by josepa on 06/10/24.
//

#ifndef VENTANA3_H
#define VENTANA3_H

#include <QWidget>
#include <QComboBox>
#include <QLabel>
#include <QVBoxLayout>
#include <QPixmap>
#include <QTime>
#include <QVector>
class MainWindow : public QWidget {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

    private slots:
        void actualizarContador();
        void iniciarContador();
        void cambiarFondo(int index);
        void crearBordeAlrededor();     // Función para crear el borde alrededor del tablero

private:
    QLabel *label1;
    QLabel *label2;
    QLabel *contadorLabel;
    QTime tiempoRestante;
    QLabel *bordeSuperior;          // QLabel para el borde superior
    QLabel *bordeInferior;          // QLabel para el borde inferior
    QLabel *bordeIzquierdo;         // QLabel para el borde izquierdo
    QLabel *bordeDerecho;           // QLabel para el borde derecho


};

#endif //VENTANA3_H
