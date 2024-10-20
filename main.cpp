#include <QApplication>
#include "ventana3.h"
#include "Graph.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    MainWindow window;
    window.setWindowTitle("Tank_Attack");
    window.show();


    return app.exec();

    Graph mapa = Graph(5,5);
    mapa.print();
    mapa.mapa_adyacencia();
    mapa.print();
    coords in = coords(0,0);
    coords out = coords(1,1 );
    //int in[2] ={1,4};
    //int out[2]= {4,2};
    cout<<mapa.Dijkstra(in,out)<<endl;
    mapa.adyacencia_mapa();


    return 0;
}


