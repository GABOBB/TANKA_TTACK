//
// Created by josepa on 06/10/24.
//

#include <QApplication>
#include <QWidget>
#include <QComboBox>
#include <QLabel>
#include <QVBoxLayout>
#include <QPixmap>
#include <QHBoxLayout>
#include <QScreen>
#include <QTimer>
#include <QTime>


#include "ventana3.h"

MainWindow::MainWindow(QWidget *parent) : QWidget(parent) {

    // Obtener el tamaño de la pantalla
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect screenGeometry = screen->geometry();
    int screenWidth = screenGeometry.width();
    int screenHeight = screenGeometry.height();

    // Ajustar la ventana al tamaño de la pantalla
    setFixedSize(screenWidth, screenHeight);

    // Crear el primer label que mostrará la imagen de fondo
    label1 = new QLabel(this);
    label1->setFixedSize(screenWidth, screenHeight);  // Ajusta el tamaño del label según la pantalla
    label1->setGeometry(0, 0, screenWidth, screenHeight); // Posición y tamaño de label1

    // Cargar una imagen inicial como fondo
    QPixmap pixmap1("/home/josepa/Imágenes/Download Boxing Ring Stage Background for free.jpeg");
    label1->setPixmap(pixmap1.scaled(label1->size(), Qt::KeepAspectRatioByExpanding));

    // Crear el segundo label que actuará como tablero de juego
    label2 = new QLabel(this);
    label2->setFixedSize(600, 400);  // Tamaño más pequeño para el tablero de juego
    label2->setStyleSheet("background-color: rgba(255, 255, 255, 0.5);");  // Fondo semi-transparente
    label2->setAlignment(Qt::AlignCenter);  // Centrar el contenido
    label2->setGeometry((screenWidth - 600) / 2, (screenHeight - 400) / 2, 600, 400); // Centrar el tablero

    crearBordeAlrededor();

    // Crear un QLabel para el contador
    contadorLabel = new QLabel(this);
    contadorLabel->setGeometry(10, 50, 200, 30);  // Posición y tamaño del label del contador
    contadorLabel->setStyleSheet("font-size: 20px; color: white;");  // Estilo del contador

    // Configurar el temporizador de 5 minutos
    tiempoRestante = QTime(0, 5, 0);  // Iniciar en 5 minutos
    contadorLabel->setText(tiempoRestante.toString("mm:ss"));

    // Crear un QTimer para contar el tiempo
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::actualizarContador);
    timer->start(1000);  // Actualizar cada segundo

    QComboBox *comboBox2 = new QComboBox(this);
    comboBox2->setFixedSize(200, 30); // Tamaño del combo box
    comboBox2->addItem("Fondo 1");
    comboBox2->addItem("Fondo 2");
    comboBox2->addItem("Fondo 3");

    // Conectar el combo box para cambiar el fondo según la selección
    connect(comboBox2, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &MainWindow::cambiarFondo);
}

void MainWindow::cambiarFondo(int index) {
    // Cambiar la imagen según el índice seleccionado en el combo box
    QPixmap pixmap1;
    switch(index) {
        case 2:
            pixmap1.load("/home/josepa/Imágenes/jpeg");
            //pixmap2.load("/home/josepa/Imágenes/Gif background for creations.gif");
            break;
        case 1:
            pixmap1.load("/home/josepa/Imágenes/Gif background for creations.gif");
            //pixmap2.load("/home/josepa/Imágenes/Seaside Beach PNG Picture, Hand Drawn Cartoon Beach Seaside Elements, Beach Clipart, Beach Seaside, Beach PNG Image For Free Download.jpeg");
            break;
        case 0:
            pixmap1.load("/home/josepa/Imágenes/Download Boxing Ring Stage Background for free.jpeg");
            //pixmap2.load("/home/josepa/Imágenes/Gif background for creations.gif");
            break;
    }
    label1->setPixmap(pixmap1.scaled(label1->size(), Qt::KeepAspectRatioByExpanding));
    //label2->setPixmap(pixmap2.scaled(label2->size(), Qt::KeepAspectRatioByExpanding));
}

void MainWindow::actualizarContador() {
    // Restar un segundo del tiempo restante
    tiempoRestante = tiempoRestante.addSecs(-1);

    // Actualizar el QLabel con el tiempo restante
    contadorLabel->setText(tiempoRestante.toString("mm:ss"));

    // Verificar si el tiempo ha llegado a cero
    if (tiempoRestante == QTime(0, 0, 0)) {
        // Detener el contador si llega a cero
        contadorLabel->setText("¡Tiempo terminado!");
    }
}

void MainWindow::crearBordeAlrededor() {
    int espesor = 10;  // Ancho del borde

    // Crear el borde superior
    bordeSuperior = new QLabel(this);
    bordeSuperior->setGeometry(label2->x() - espesor, label2->y() - espesor, label2->width() + 2 * espesor, espesor);
    bordeSuperior->setStyleSheet("background-color: black;");

    // Crear el borde inferior
    bordeInferior = new QLabel(this);
    bordeInferior->setGeometry(label2->x() - espesor, label2->y() + label2->height(), label2->width() + 2 * espesor, espesor);
    bordeInferior->setStyleSheet("background-color: black;");

    // Crear el borde izquierdo
    bordeIzquierdo = new QLabel(this);
    bordeIzquierdo->setGeometry(label2->x() - espesor, label2->y(), espesor, label2->height());
    bordeIzquierdo->setStyleSheet("background-color: black;");

    // Crear el borde derecho
    bordeDerecho = new QLabel(this);
    bordeDerecho->setGeometry(label2->x() + label2->width(), label2->y(), espesor, label2->height());
    bordeDerecho->setStyleSheet("background-color: black;");
}
