#include <QApplication>
#include <ctime>
#include <cstdlib>
#include "ventana3.h"
#include "Graph.h"

std::vector<std::vector<int>> generate_Mapa() {
    vector<vector<int>> M_mapa(20, vector<int>(20, 0));
    srand(time(NULL));
    for (int i = 1; i < 20-1; i++) {
        for (int j = 1; j < 20-1; j++) {
            int ranInt = (rand() % 100) + 1;
            if(ranInt>=15) {
                M_mapa[i][j] = 1;
            }
        }
    }
    return M_mapa;
}


int main(int argc, char *argv[]) {
    vector<vector<int>> M_mapa =generate_Mapa();
        /*{{0,0,0,1},
                                    {0,1,0,1},
                                    {0,1,1,1},
                                    {0,0,0,1},
                                    {0,0,0,0},
                                    {0,0,0,0},
                                    {0,0,0,0},
                                    {0,0,0,0},
                                    {0,0,0,0}};*/
                                //

    /**/
    Graph mapa = Graph(M_mapa.size(),M_mapa[0].size());
    //mapa.print();
    mapa.mapa_adyacencia(M_mapa);
    //mapa.adyacencia_mapa();
    coords in = coords(1,1);
    coords out = coords(2,4);

    cout<<mapa.AStar(in,out)<<endl;




    QApplication app(argc, argv);

    MainWindow window(M_mapa);
    window.setWindowTitle("Tank_Attack");

    window.show();

    return app.exec();

 /*   return 0; */
}


/*
     \/
     /\
    /  \
  \/[][]\/
  /\[][]/\
    \  /
     \/
     /\
*/