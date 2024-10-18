//
// Created by gbb on 28/09/24.
//

#ifndef GRAFO_H
#define GRAFO_H
#include <iostream>
#include <vector>
using namespace std;
struct coords {
    int i, j;
    coords(int i, int j) : i(i), j(j) {}
};

class Graph {
    vector<vector<int>> Matriz_Adyacencia;

    int filas;
    int columnas;

public:
        Graph(int x, int y);

        void print();
        void agregar_arista(int peso, int n, int m);
        void mapa_adyacencia();
        void adyacencia_mapa();

        string Linea_Vista(coords in,coords out,bool chocado);
        string Linea_Vista_aux(coords in,coords out, bool c);

        void BFS(int in, int out);
        void Dijkstra(int in, int out);
};



#endif //GRAFO_H
