#include <iostream>
#include "Graph.h"

int main(){
    Graph mapa = Graph(4,4);
    mapa.print();
    mapa.mapa_adyacencia();
    mapa.print();

    int in[2] ={0,0};
    int out[2] ={1,2};
    cout<<mapa.Linea_Vista(in,out,false)<<endl;
    mapa.adyacencia_mapa();


    return 0;
}
/*
 mapa.agregar_arista(1,2,1);
    mapa.agregar_arista(1,1,3);
    mapa.agregar_arista(1,6,9);
    mapa.agregar_arista(1,9,4);
    mapa.agregar_arista(1,4,3);
*/