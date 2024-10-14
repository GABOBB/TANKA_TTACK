#include <iostream>
#include "Graph.h"

int main(){
    Graph mapa = Graph(5,5);
    mapa.print();
    mapa.mapa_adyacencia();
    mapa.print();

    int in[2] ={2,4};
    int out[2]= {2,1};
    cout<<mapa.Linea_Vista(in,out,true)<<endl;
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