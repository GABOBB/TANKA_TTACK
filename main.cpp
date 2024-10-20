#include <QApplication>
#include "ventana3.h"
#include "Graph.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    MainWindow window;
    window.setWindowTitle("Tank_Attack");
    window.show();
    vector<vector<int>> M_mapa = {
                            {1,1,1,1,1},
                            {1,1,1,1,1},
                            {1,1,0,1,1},
                            {1,1,0,1,1},
                            {1,1,0,1,1}};
    Graph mapa = Graph(5,5);
    mapa.print();
    mapa.mapa_adyacencia(M_mapa);
    mapa.print();
    coords in = coords(0,0);
    coords out = coords(2,1 );
    //int in[2] ={1,4};
    //int out[2]= {4,2};
    cout<<mapa.Linea_Vista_tanque(in,out,true)<<endl;

    return app.exec();


}

/*

    mapa.adyacencia_mapa();
    */