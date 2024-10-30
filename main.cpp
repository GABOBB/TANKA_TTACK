#include <QApplication>
#include <ctime>
#include <cstdlib>
#include "ventana3.h"
#include "Graph.h"

std::vector<std::vector<int>> generate_Mapa() {
    vector<vector<int>> M_mapa = {
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 ,0 ,0 ,0 ,0 ,0, 0, 0, 0, 0, 0, 0 ,0 ,0 ,0 ,0 ,0 ,0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 ,0 ,0 ,0 ,0 ,0, 0, 0, 0, 0, 0, 0 ,0 ,0 ,0 ,0 ,0 ,0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 ,0 ,0 ,0 ,0 ,0, 0, 0, 0, 0, 0, 0 ,0 ,0 ,0 ,0 ,0 ,0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 ,0 ,0 ,0 ,0 ,0, 0, 0, 0, 0, 0, 0 ,0 ,0 ,0 ,0 ,0 ,0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 ,0 ,0 ,0 ,0 ,0, 0, 0, 0, 0, 0, 0 ,0 ,0 ,0 ,0 ,0 ,0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 ,0 ,0 ,0 ,0 ,0, 0, 0, 0, 0, 0, 0 ,0 ,0 ,0 ,0 ,0 ,0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 ,0 ,0 ,0 ,0 ,0, 0, 0, 0, 0, 0, 0 ,0 ,0 ,0 ,0 ,0 ,0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 ,0 ,0 ,0 ,0 ,0, 0, 0, 0, 0, 0, 0 ,0 ,0 ,0 ,0 ,0 ,0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 ,0 ,0 ,0 ,0 ,0, 0, 0, 0, 0, 0, 0 ,0 ,0 ,0 ,0 ,0 ,0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 ,0 ,0 ,0 ,0 ,0, 0, 0, 0, 0, 0, 0 ,0 ,0 ,0 ,0 ,0 ,0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 ,0 ,0 ,0 ,0 ,0, 0, 0, 0, 0, 0, 0 ,0 ,0 ,0 ,0 ,0 ,0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 ,0 ,0 ,0 ,0 ,0, 0, 0, 0, 0, 0, 0 ,0 ,0 ,0 ,0 ,0 ,0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 ,0 ,0 ,0 ,0 ,0, 0, 0, 0, 0, 0, 0 ,0 ,0 ,0 ,0 ,0 ,0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 ,0 ,0 ,0 ,0 ,0, 0, 0, 0, 0, 0, 0 ,0 ,0 ,0 ,0 ,0 ,0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 ,0 ,0 ,0 ,0 ,0, 0, 0, 0, 0, 0, 0 ,0 ,0 ,0 ,0 ,0 ,0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 ,0 ,0 ,0 ,0 ,0, 0, 0, 0, 0, 0, 0 ,0 ,0 ,0 ,0 ,0 ,0}};
    srand(time(NULL));
    for (int i = 1; i < M_mapa.size()-1; i++) {
        for (int j = 1; j < M_mapa[0].size()-1; j++) {
            int ranInt = (rand() % 100) + 1;
            if(ranInt>=15) {
                M_mapa[i][j] = 1;
            }
        }
    }
    return M_mapa;
}


int main(int argc, char *argv[]) {

    vector<vector<int>> M_mapa = generate_Mapa();

    /**/
    Graph mapa = Graph(M_mapa.size(),M_mapa[0].size());
    //mapa.print();
    mapa.mapa_adyacencia(M_mapa);
    //mapa.print();
    coords in = coords(1,1);
    coords out = coords(1,5);

    cout<<mapa.Dijkstra(in,out)<<endl;






    QApplication app(argc, argv);

    MainWindow window(M_mapa);
    window.setWindowTitle("Tank_Attack");

    window.show();

    return app.exec();

    /*  return 0;*/
}

