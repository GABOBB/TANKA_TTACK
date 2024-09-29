#include <iostream>
#include "Graph.h"

int main(){
    Graph mapa;
    mapa.print();
    //mapa.agregar_arista(2,6,6);
    mapa.agregar_arista(2,4,4);
    mapa.agregar_arista(2,3,3);
    mapa.print();
    return 0;
}
