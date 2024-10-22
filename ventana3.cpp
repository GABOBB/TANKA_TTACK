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
#include <QDebug>



#include "ventana3.h"

#include <iostream>


QTimer *timer;

MainWindow::MainWindow(std::vector<std::vector<int>> Matriz, QWidget *parent) : QWidget(parent) {
    this->Matriz = Matriz;
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
    QPixmap pixmap1("../photos/box.jpeg");
    label1->setPixmap(pixmap1.scaled(label1->size(), Qt::KeepAspectRatioByExpanding));

    // Crear el segundo label que actuará como tablero de juego
    label2 = new QLabel(this);
    label2->setFixedSize(800, 500);  // Tamaño más pequeño para el tablero de juego
    label2->setStyleSheet("background-color: rgba(255, 255, 255, 0.5);");  // Fondo semi-transparente
    label2->setAlignment(Qt::AlignCenter);  // Centrar el contenido
    label2->setGeometry((screenWidth - 800) / 2, (screenHeight - 500) / 2, 800, 500); // Centrar el tablero


    crearBordeAlrededor();
    // Llenar el tablero con la matriz
    llenarTablero(Matriz);
    agregarTanques(Matriz);


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


void MainWindow::llenarTablero(const std::vector<std::vector<int>>& matriz) {
    QGridLayout *gridLayout = new QGridLayout(label2);
    gridLayout->setSpacing(0);

    QPixmap imagenCero("../photos/coble2.jpeg");

    for (int i = 0; i < matriz.size(); ++i) {
        for (int j = 0; j < matriz[i].size(); ++j) {
            QLabel *cellLabel = new QLabel();
            cellLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

            if (matriz[i][j] == 0) {
                cellLabel->setPixmap(imagenCero.scaled(
                    cellLabel->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
                cellLabel->setAlignment(Qt::AlignCenter);
            } else {
                cellLabel->setStyleSheet("background-color: transparent;");  // Asegurarse de que no haya fondo
            }

            gridLayout->addWidget(cellLabel, i, j);
        }
    }
}


void MainWindow::cambiarFondo(int index) {
    // Cambiar la imagen según el índice seleccionado en el combo box
    QPixmap pixmap1;
    switch(index) {
        case 2:

            pixmap1.load("../photos/jpeg");

            //pixmap2.load("/home/josepa/Imágenes/Gif background for creations.gif");
            break;
        case 1:
            pixmap1.load("../photos/.gif");
            //pixmap2.load("/home/josepa/Imágenes/Seaside Beach PNG Picture, Hand Drawn Cartoon Beach Seaside Elements, Beach Clipart, Beach Seaside, Beach PNG Image For Free Download.jpeg");
            break;
        case 0:
            pixmap1.load("../photos/box.jpeg");
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

    // Crear el borde agregarTanquesderecho
    bordeDerecho = new QLabel(this);
    bordeDerecho->setGeometry(label2->x() + label2->width(), label2->y(), espesor, label2->height());
    bordeDerecho->setStyleSheet("background-color: black;");
}
using namespace std;
void MainWindow::agregarTanques(const std::vector<std::vector<int>> &matriz) {
    Posicion P = buscarEspacio();


    // Rutas de las imágenes de los tanques
    QString rutaTanqueRojo = "../photos/tanque_rojo.png";
    QString rutaTanqueAzul = "../photos/tanque_azul.png";
    QString rutaTanqueAmarillo = "../photos/tanque_amarillo.png";
    QString rutaTanqueCeleste = "../photos/tanque_celeste.png";

    crearLabelTanque(P.fila[0],P.columna[0],rutaTanqueRojo,"tanque Rojo 1");
    crearLabelTanque(P.fila[1],P.columna[1],rutaTanqueRojo,"tanque Rojo 2");

    crearLabelTanque(P.fila[2],P.columna[2],rutaTanqueAzul,"tanque Azul 1");
    crearLabelTanque(P.fila[3],P.columna[3],rutaTanqueAzul,"tanque Azul 2");

    crearLabelTanque(P.fila[4],P.columna[4],rutaTanqueAmarillo,"tanque Amarillo 1");
    crearLabelTanque(P.fila[5],P.columna[5],rutaTanqueAmarillo,"tanque Amarilla 2");

    crearLabelTanque(P.fila[6],P.columna[6],rutaTanqueCeleste,"tanque Celeste 1");
    crearLabelTanque(P.fila[7],P.columna[7],rutaTanqueCeleste,"tanque Celeste 2");

 /*
    // Buscar las posiciones válidas
    Posicion posRojo = buscarEspacio(matriz, 1, 2);
    Posicion posAzul = buscarEspacio(matriz, 1, 2, posRojo.fila);
    Posicion posAmarillo = buscarEspacio(matriz, matriz[0].size() - 3, matriz[0].size() - 1);
    Posicion posCeleste = buscarEspacio(matriz, matriz[0].size() - 3, matriz[0].size() - 1, posAmarillo.fila);

    // Crear los labels solo si las posiciones son válidas
    if (posRojo.fila != -1) crearLabelTanque(posRojo, rutaTanqueRojo, "Tanque Rojo");
    if (posAzul.fila != -1) crearLabelTanque(posAzul, rutaTanqueAzul, "Tanque Azul");
    if (posAmarillo.fila != -1) crearLabelTanque(posAmarillo, rutaTanqueAmarillo, "Tanque Amarillo");
    if (posCeleste.fila != -1) crearLabelTanque(posCeleste, rutaTanqueCeleste, "Tanque Celeste");
    */
}

void MainWindow::crearLabelTanque(int i,int j, const QString &rutaImagen, const QString &nombre) {
    QLabel *labelTanque = new QLabel();  // Crear el QLabel para el tanque
    QPixmap pixmap(rutaImagen);

    labelTanque->setPixmap(pixmap.scaled(50, 50, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    labelTanque->setAlignment(Qt::AlignCenter);
    labelTanque->setToolTip(nombre);

    // Establecer un fondo para hacer el tanque visible
    labelTanque->setStyleSheet("background-color: transparent;"); // Cambiar a "white" si es necesario

    // Asegurarse de que el layout está correctamente asignado
    QGridLayout *gridLayout = qobject_cast<QGridLayout *>(label2->layout());
    if (gridLayout) {
        gridLayout->addWidget(labelTanque, i, j);
    } else {
        qDebug() << "Error: No se pudo acceder al QGridLayout.";
    }
}



Posicion MainWindow::buscarEspacio() {
    int contador = 0;
    Posicion p;
    for(int x=1;x<3;x++) {
        for(int i=1; i<this->Matriz.size(); i++) {
            if(Matriz[i][x] == 1 && contador<4){
                p.fila[contador] = i;
                p.columna[contador] = x;
                contador++;
            }
        }
    }
    for(int x=Matriz[0].size()-2; x<Matriz[0].size(); x++) {
        for(int i=1; i<Matriz.size(); i++) {
            if(Matriz[i][x] == 1 && contador<8) {
                p.fila[contador] = i;
                p.columna[contador] = x;
                contador++;
            }
        }
    }
    return p;
}