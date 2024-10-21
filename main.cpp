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
    QApplication app(argc, argv);

    MainWindow window;
    window.setWindowTitle("Tank_Attack");
    window.show();
    vector<vector<int>> M_mapa = {
        {1,1,1,1,1},
        {1,0,0,1,1},
        {1,1,0,1,1},
        {1,1,0,1,1},
        {1,1,0,1,1}};
    Graph mapa = Graph(5,5);
    mapa.print();
    mapa.mapa_adyacencia(M_mapa);
    mapa.print();
    coords in = coords(4,0);
    coords out = coords(4,4 );

    cout<<mapa.Dijkstra(in,out)<<endl;

    return app.exec();


}
