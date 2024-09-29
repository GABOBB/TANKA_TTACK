//
// Created by gbb on 28/09/24.
//

#include "Graph.h"
using namespace std;

Graph::Graph(){
  int n = 5; int m = 10;
    Matriz_Adyacencia = vector<vector<int>>(n,vector<int>(m,0));
}

void Graph::print(){
      cout << "matriz de adyacencia:" << endl;
      for(int i=0;i<Matriz_Adyacencia.size();i++){
           for(int j=0;j<Matriz_Adyacencia[i].size();j++){
               cout << Matriz_Adyacencia[i][j] << " ";
           }
           cout << endl;
      }
}

void Graph::agregar_arista(int peso, int n, int m){

    Matriz_Adyacencia[n][m] = peso;
    Matriz_Adyacencia[m][n] = peso;
};