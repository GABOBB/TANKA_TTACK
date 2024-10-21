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
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 1, 1, 1, 1, 1, 0, 0},
        {0, 1, 0, 1, 1, 1, 1, 0},
        {0, 1, 1, 0, 1, 1, 1, 0},
        {0, 0, 1, 1, 0, 0, 0, 0},
        {0, 1, 1, 1, 0, 1, 1, 0},
        {0, 1, 1, 1, 1, 1, 1, 0},
        {0, 0, 0, 0, 0, 0, 0, 0}
    };
    Graph mapa = Graph(M_mapa.size(),M_mapa[0].size());
    mapa.print();
    mapa.mapa_adyacencia(M_mapa);
    mapa.print();
    coords in = coords(1,1);
    coords out = coords(5,5 );

    cout<<mapa.AStar(in,out)<<endl;

/*

    QApplication app(argc, argv);

    MainWindow window(M_mapa);
    window.setWindowTitle("Tank_Attack");

    window.show();

    return app.exec();
*/
      return 0;
}
