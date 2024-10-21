#include <QApplication>
#include "ventana3.h"
#include "Graph.h"

/*

    mapa.adyacencia_mapa();

     \/
     /\
    /  \
  \/[][]\/
  /\[][]/\
    \  /
     \/
     /\
*/
int main(int argc, char *argv[]) {

    vector<vector<int>> M_mapa = {
        {1,1,1,1,1},
        {1,1,0,0,1},
        {1,1,0,1,1},
        {1,1,0,1,1},
        {1,1,0,1,1}};
    Graph mapa = Graph(5,5);
    mapa.print();
    mapa.mapa_adyacencia(M_mapa);
    mapa.print();
    coords in = coords(4,0);
    coords out = coords(2,4 );

    cout<<mapa.Linea_Vista_tanque(in,out, true)<<endl;



    QApplication app(argc, argv);

    MainWindow window(M_mapa);
    window.setWindowTitle("Tank_Attack");

    window.show();

    return app.exec();

     /*  return 0;*/
}
