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
#include <vector>
#include "Graph.h"
#include <QMouseEvent>


using namespace std;
struct Posicion {
    int fila[8];
    int columna[8];
};

class MainWindow : public QWidget {
    Q_OBJECT
    vector<vector<int>> Matriz;
    vector<QLabel*> tanques;
    int tanke=-1;

public:
    MainWindow(std::vector<std::vector<int>>Matriz ,QWidget *parent = nullptr);

    private slots:
        void actualizarContador();
        void iniciarContador();
        void cambiarFondo(int index);
        void crearBordeAlrededor();     // Función para crear el borde alrededor del tablero
        void llenarTablero(const std::vector<std::vector<int>>& matriz);
    // Nuevos métodos para manejar los tanques
        void agregarTanques(const std::vector<std::vector<int>> &matriz);  // Añadir los labels de los tanques
    // Definir valor por defecto aquí (en el .h)
        Posicion buscarEspacio();

        void crearLabelTanque(int i,int j, const QString &rutaImagen, const QString &nombre);
        void tanqueClicked(const QString &nombre);
protected:
    void mousePressEvent(QMouseEvent *event) override;
    void MovimientoDeTanque(int i, int j);

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
