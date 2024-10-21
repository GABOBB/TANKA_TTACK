//
// Created by gbb on 28/09/24.
//

#ifndef GRAFO_H
#define GRAFO_H
#include <iostream>     // Para imprimir en consola con std::cout
#include <vector>       // Para utilizar std::vector en la representación de la matriz de adyacencia
#include <queue>        // Para usar std::priority_queue en los algoritmos de A* y Dijkstra
#include <cmath>        // Para funciones matemáticas como std::abs y std::sqrt (para calcular distancias)
#include <climits>      // Para usar INT_MAX (valor máximo de un entero)
#include <unordered_set> // Para almacenar nodos visitados en el algoritmo A*
#include <unordered_map> // Para guardar padres y costos en A* y Dijkstra
#include <cstdlib>      // Para generar números aleatorios en srand y rand
#include <ctime>        // Para inicializar srand con la función time(NULL)


using namespace std;
struct coords {
    int i, j;
    coords()= default;
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
        void mapa_adyacencia(vector<vector<int>>& mapa);
        void adyacencia_mapa();

        string Linea_Vista_bala(coords in,coords out,bool c);
        string Linea_Vista_tanque(coords in,coords out, bool c);
        string Dijkstra(coords in, coords out);
        string AStar(coords in, coords out);

        void BFS(int in, int out);
        void Dijkstra(int in, int out);
};



#endif //GRAFO_H
