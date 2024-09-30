//
// Created by gbb on 28/09/24.
//

#include "Graph.h"
using namespace std;

Graph::Graph(){
  int n = 10; int m = 10;
    Matriz_Adyacencia = vector<vector<int>>(n,vector<int>(m,0));
}

void Graph::print(){
      cout <<"~~~~~~~~~~~~~~~~~~~~inicio matriz de adyacencia~~~~~~~~~~~~~~~~~~~~" << endl;
      for(int i=0;i<Matriz_Adyacencia.size();i++){
           for(int j=0;j<Matriz_Adyacencia[i].size();j++){
               cout << Matriz_Adyacencia[i][j] << "  ";
           }
           cout << endl;
      }
      cout << "~~~~~~~~~~~~~~~~~~~~final matriz de adyacencia~~~~~~~~~~~~~~~~~~~~" << endl;
}

void Graph::agregar_arista(int peso, int n, int m){
  if(n>Matriz_Adyacencia.size() || m>Matriz_Adyacencia[0].size()){
    cout<<"fuera de alcance"<<endl;
    return;
  }
    Matriz_Adyacencia[n][m] = peso;
    Matriz_Adyacencia[m][n] = peso;
};