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
#include <QPushButton>


#include "ventana3.h"

// Definimos la matriz
const int filas = 8;
const int columnas = 8;
int MT[filas][columnas] = {
    {1, 0, 1, 1, 1, 0, 1, 1},
    {1, 1, 1, 1, 1, 1, 0, 1},
    {1, 1, 0, 1, 1, 1, 1, 1},
    {1, 1, 1, 0, 1, 1, 1, 1},
    {1, 0, 1, 1, 1, 1, 0, 1},
    {1, 1, 1, 1, 0, 1, 1, 1},
    {1, 0, 1, 1, 1, 1, 1, 0},
    {0, 1, 1, 1, 1, 0, 1, 1}
};

QTimer *timer;

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
    label2->setFixedSize(800, 500);  // Tamaño más pequeño para el tablero de juego
    label2->setStyleSheet("background-color: rgba(255, 255, 255, 0.5);");  // Fondo semi-transparente
    label2->setAlignment(Qt::AlignCenter);  // Centrar el contenido
    label2->setGeometry((screenWidth - 800) / 2, (screenHeight - 500) / 2, 800, 500); // Centrar el tablero

    // Crear el QGridLayout y añadirlo a label2
    QGridLayout *gridLayout = new QGridLayout(label2);
    gridLayout->setSpacing(0);  // Espacio entre los elementos


    // Distribuir las celdas de forma uniforme
    for (int i = 0; i < filas; ++i) {
        gridLayout->setRowStretch(i, 1);  // Misma altura para cada fila
    }
    for (int j = 0; j < columnas; ++j) {
        gridLayout->setColumnStretch(j, 1);  // Misma anchura para cada columna
    }

    // Cargar la imagen que se mostrará para los ceros
    QPixmap imagenCero("/home/josepa/Escritorio/TANK_ATTACK/photos/coble2.jpeg");

    // Rellenar el tablero
    for (int i = 0; i < filas; ++i) {
        for (int j = 0; j < columnas; ++j) {
            QLabel *cellLabel = new QLabel();
            cellLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

            if (MT[i][j] == 0) {
                // Establecer la imagen escalada para que ocupe toda la casilla
                cellLabel->setPixmap(imagenCero.scaled(
                    cellLabel->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
                cellLabel->setAlignment(Qt::AlignCenter);  // Alinear la imagen al centro
            } else {
                cellLabel->setStyleSheet("background-color: transparent;");  // Casilla vacía
            }

            // Agregar el QLabel al layout
            gridLayout->addWidget(cellLabel, i, j);
        }
    }



    crearBordeAlrededor();



    // Crear un QLabel para el contador
    contadorLabel = new QLabel(this);
    contadorLabel->setGeometry(10, 50, 200, 30);  // Posición y tamaño del label del contador
    contadorLabel->setStyleSheet("font-size: 20px; color: white;");  // Estilo del contador

    // Configurar el temporizador de 5 minutos
    tiempoRestante = QTime(0, 5, 0);  // Iniciar en 5 minutos
    contadorLabel->setText(tiempoRestante.toString("mm:ss"));

    // Crear el QTimer pero no iniciarlo aún
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::actualizarContador);

    // Crear el botón de inicio del contador
    QPushButton *startButton = new QPushButton("Iniciar Partida", this);
    startButton->setGeometry(10, 100, 200, 30);  // Posición y tamaño
    connect(startButton, &QPushButton::clicked, this, &MainWindow::iniciarContador);

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
            pixmap1.load("/home/josepa/Escritorio/TANK_ATTACK/photos/jpeg");
            //pixmap2.load("/home/josepa/Imágenes/Gif background for creations.gif");
            break;
        case 1:
            pixmap1.load("/home/josepa/Escritorio/TANK_ATTACK/photos/.gif");
            //pixmap2.load("/home/josepa/Imágenes/Seaside Beach PNG Picture, Hand Drawn Cartoon Beach Seaside Elements, Beach Clipart, Beach Seaside, Beach PNG Image For Free Download.jpeg");
            break;
        case 0:
            pixmap1.load("/home/josepa/Escritorio/TANK_ATTACK/photos/box.jpeg");
            //pixmap2.load("/home/josepa/Imágenes/Gif background for creations.gif");
            break;
    }
    label1->setPixmap(pixmap1.scaled(label1->size(), Qt::KeepAspectRatioByExpanding));
    //label2->setPixmap(pixmap2.scaled(label2->size(), Qt::KeepAspectRatioByExpanding));
}

// Función para iniciar el contador al presionar el botón
void MainWindow::iniciarContador() {
    timer->start(1000);  // El timer se actualiza cada segundo
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
