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

    int filas;
    int columnas;

public:
        Graph(int x, int y);

        void print();
        void agregar_arista(int peso, int n, int m);
        void mapa_adyacencia();
        void adyacencia_mapa();

        string Linea_Vista(int in[2],int out[2],bool chocado);
        string Linea_Vista_aux(int in[2],int out[2]);

        void BFS(int in, int out);
        void Dijkstra(int in, int out);
};



#endif //GRAFO_H
