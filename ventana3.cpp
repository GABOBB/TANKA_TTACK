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
#include <QPropertyAnimation>
#include <QSequentialAnimationGroup>
#include <QMouseEvent>



#include "ventana3.h"

#include <iostream>


QTimer *timer;

MainWindow::MainWindow(std::vector<std::vector<int>> Matriz, QWidget *parent) : QWidget(parent), mapa(Graph(Matriz.size(), Matriz[0].size())) {
    mapa.mapa_adyacencia(Matriz);
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
    label1->setFixedSize(screenWidth, screenHeight); // Ajusta el tamaño del label según la pantalla
    label1->setGeometry(0, 0, screenWidth, screenHeight); // Posición y tamaño de label1

    // Cargar una imagen inicial como fondo
    QPixmap pixmap1("../photos/box.jpeg");
    label1->setPixmap(pixmap1.scaled(label1->size(), Qt::KeepAspectRatioByExpanding));

    // Crear el segundo label que actuará como tablero de juego
    label2 = new QLabel(this);
    label2->setFixedSize(800, 500); // Tamaño más pequeño para el tablero de juego
    label2->setStyleSheet("background-color: rgba(255, 255, 255, 0.5);"); // Fondo semi-transparente
    label2->setAlignment(Qt::AlignCenter); // Centrar el contenido
    label2->setGeometry((screenWidth - 800) / 2, (screenHeight - 500) / 2, 800, 500); // Centrar el tablero


    crearBordeAlrededor();
    // Llenar el tablero con la matriz
    llenarTablero(Matriz);
    agregarTanques(Matriz);


    // Crear un QLabel para el contador
    contadorLabel = new QLabel(this);
    contadorLabel->setGeometry(10, 50, 200, 30); // Posición y tamaño del label del contador
    contadorLabel->setStyleSheet("font-size: 20px; color: white;"); // Estilo del contador

    // Configurar el temporizador de 5 minutos
    tiempoRestante = QTime(0, 5, 0); // Iniciar en 5 minutos
    contadorLabel->setText(tiempoRestante.toString("mm:ss"));

    // Crear el QTimer pero no iniciarlo aún
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MainWindow::actualizarContador);

    // Crear el botón de inicio del contador
    QPushButton *startButton = new QPushButton("Iniciar Partida", this);
    startButton->setGeometry(10, 100, 200, 30); // Posición y tamaño
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
    gridLayout->setSpacing(0.1);

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
    crearLabelTanque(P.fila[5],P.columna[5],rutaTanqueAmarillo,"tanque Amarillp 2");

    crearLabelTanque(P.fila[6],P.columna[6],rutaTanqueCeleste,"tanque Celeste 1");
    crearLabelTanque(P.fila[7],P.columna[7],rutaTanqueCeleste,"tanque Celeste 2");

    for(int i=0;i<8;i++) {
        Matriz[P.fila[i]][P.columna[i]] = 2;
    }

    for(int i=0;i<Matriz.size();i++) {
        for(int j=0;j<Matriz[i].size();j++) {
            cout<<Matriz[i][j]<<" ";
        }
        cout<<endl;
    }
}

void MainWindow::crearLabelTanque(int i,int j, const QString &rutaImagen, const QString &nombre) {
    QLabel *labelTanque = new QLabel();  // Crear el QLabel para el tanque
    QPixmap pixmap(rutaImagen);

    labelTanque->setPixmap(pixmap.scaled(50, 50, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    labelTanque->setAlignment(Qt::AlignCenter);
    labelTanque->setToolTip(nombre);

    // Establecer un fondo para hacer el tanque visible
    labelTanque->setStyleSheet("background-color: transparent;"); // Cambiar a "white" si es necesario
    tanques.push_back(labelTanque);
    // Asegurarse de que el layout está correctamente asignado
    QGridLayout *gridLayout = qobject_cast<QGridLayout *>(label2->layout());
    if (gridLayout) {
        gridLayout->addWidget(labelTanque, i, j);

    } else {
        qDebug() << "Error: No se pudo acceder al QGridLayout.";
    }
}

void MainWindow::tanqueClicked(const QString &nombre) {

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

void MainWindow::mousePressEvent(QMouseEvent *event) {
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect screenGeometry = screen->geometry();
    int screenWidth = screenGeometry.width();
    int screenHeight = screenGeometry.height();

    int x = (event->x()) - (screenWidth - 800) / 2;
    int y = (event->y()) - (screenHeight - 500) / 2;
    int x2 = x / tanques[0]->geometry().width();
    int y2 = y / tanques[0]->geometry().height();

    static QLabel* selectedTank = nullptr;
    static bool isFirstClick = true;

    if (event->button() == Qt::LeftButton) {
        if (isFirstClick) {
            for (QLabel* tanque : tanques) {
                if (tanque->geometry().contains(x, y)) {
                    qDebug() << "Tanque seleccionado:" << tanque->toolTip();
                    //if (tanque->toolTip().contains("Rojo") || tanque->toolTip().contains("Amarillo")) {
                        selectedTank = tanque;
                        isFirstClick = false; // Primer clic completado

                        break;
                    //}else if(tanque->toolTip().contains("Celeste") || tanque->toolTip().contains("Azul")) {
                   //     selectedTank = tanque;
                   //     isFirstClick = false; // Primer clic completado

                   //     break;
                   // }
                }
            }
        } else {
            // Segundo clic - verificar que el espacio en la matriz es válido
            if (x2 >= 0 && x2 < Matriz[0].size() && y2 >= 0 && y2 < Matriz.size()) { // Verificar límites de la matriz
                int cellValue = Matriz[y2][x2];
                if (cellValue == 1 && selectedTank) {  // Solo mover si es un espacio vacío
                    qDebug()<< y2 << " - " << x2<<endl;
                    QPoint start = selectedTank->geometry().topLeft();
                    QPoint end(x, y);
                    moveTankAlongPath(selectedTank, start, end); // Llamar a tu algoritmo de movimiento

                    selectedTank = nullptr;
                    isFirstClick = true;
                } else {
                    qDebug() << "Movimiento no permitido, espacio ocupado o restringido.";
                }
            }
        }
    }

    QWidget::mousePressEvent(event);
}


void MainWindow::moveTankAlongPath(QLabel* tanque, const QPoint& start, const QPoint& end) {
    cout<< start.x() <<"-"<<start.y() <<"---"<<end.x()<<"-"<<end.y()<<endl;
    QScreen *screen = QGuiApplication::primaryScreen();
    QRect screenGeometry = screen->geometry();
    int screenWidth = screenGeometry.width();
    int screenHeight = screenGeometry.height();
    coords start__ = coords(start.y()- (screenHeight - 500) / 2, start.x()-(screenWidth-800)/2);
    coords end__ = coords(end.y()- (screenHeight - 500) / 2, end.x()-(screenWidth-800)/2);
    srand(time(NULL));
    int ranInt = (rand() % 100) + 1;
    string ruta;
    //cout<<start__.i<<" --------------------- "<<start__.j<<endl;
    if(tanque->toolTip().contains("Amarillo") || tanque->toolTip().contains("Rojo")) {
        if(ranInt>=80) {
            cout<<"dijkstra"<<endl;
            ruta = mapa.Dijkstra(start__,end__);
        }else {
            cout<<"aleatorio"<<endl;

        }
    }else {
        if(ranInt>=50) {
            cout<<"bfs"<<endl;
        }else {
            cout<<"aleatorio"<<endl;
        }
    }
    // Ruta generada por tu algoritmo (ejemplo de puntos intermedios)
    QList<QPoint> pathPoints = calculatePath(start, end, "");  // Implementa o llama a tu algoritmo aquí

    // Grupo de animación para coordinar los movimientos entre puntos
    QSequentialAnimationGroup *animationGroup = new QSequentialAnimationGroup(this);

    // Crear animaciones para cada tramo de la ruta
    for (int i = 0; i < pathPoints.size() - 1; ++i) {
        QPropertyAnimation *animation = new QPropertyAnimation(tanque, "pos");
        animation->setDuration(200);  // Duración en ms para cada tramo (ajustable)
        animation->setStartValue(pathPoints[i]);
        animation->setEndValue(pathPoints[i + 1]);
        animationGroup->addAnimation(animation);
    }

    // Iniciar la animación
    connect(animationGroup, &QSequentialAnimationGroup::finished, animationGroup, &QSequentialAnimationGroup::deleteLater);
    animationGroup->start();
}

// Ejemplo de una función que calcula la ruta entre dos puntos
QList<QPoint> MainWindow::calculatePath(const QPoint& start, const QPoint& end, const string ruta) {
    QList<QPoint> path;
    path.append(start);
    QPoint temp = start;
    for (int i = 0; i < ruta.length(); i++) {
        if(ruta[i] == 'U') {
        temp = QPoint(temp.y()+tanques[0]->geometry().height(),temp.x());
        path.append(temp);
        }else if(ruta[i] == 'D') {

        }else if(ruta[i] == 'R') {

        }else if(ruta[i] == 'L') {

        }else if(ruta[i] == 'A') {

        }else if(ruta[i] == 'a') {

        }else if(ruta[i] == 'B') {

        }else if(ruta[i] == 'b') {

        }

    }
    //Mi loco, en esa QList es donde hay que conectarlo con los algoritmos

    // Aquí puedes añadir los puntos intermedios de la ruta que ya tengas definida


    // Este es solo un ejemplo de puntos; en tu caso, debes llamar a tus algoritmos de ruta.
    path.append(QPoint((start.x() + end.x()) / 2, start.y()));  // Punto intermedio ejemplo
    path.append(end);

    return path;
}



void MainWindow::MovimientoDeTanque(int i, int j) {
    if(this->tanke == -1) {

    }
}