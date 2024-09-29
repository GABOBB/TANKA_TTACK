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

    public:
        Graph();

        void print();
        void agregar_arista(int peso, int n, int m);
};



#endif //GRAFO_H
