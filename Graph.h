//
// Created by gbb on 28/09/24.
//

#ifndef GRAFO_H
#define GRAFO_H
#include <iostream>
#include <vector>
using namespace std;

class Graph {
    vector<vector<int>> Matriz_Adyacencia;
    int columnas = 0;
    int filas = 0;

    public:
        Graph(int x, int y);

        void print();
        void agregar_arista(int peso, int n, int m);
        void mapa_adyacencia();
        void adyacencia_mapa();
};



#endif //GRAFO_H
