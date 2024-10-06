#include <QApplication>
#include "ventana3.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    MainWindow window;
    window.setWindowTitle("Tank_Attack");
    window.show();


    return app.exec();
}