#include <iostream>
#include "Graph.h"

int main(){
    Graph mapa;
    mapa.print();

    mapa.agregar_arista(1,2,1);
    mapa.agregar_arista(1,1,3);
    mapa.agregar_arista(1,6,9);
    mapa.agregar_arista(1,9,4);
    mapa.agregar_arista(1,4,3);

    mapa.print();
    return 0;
}
