//
// Created by gbb on 28/09/24.
//

#include "Graph.h"
using namespace std;

Graph::Graph(int x, int y){
  filas = x;
  columnas = y;

  int n = x*y;
    Matriz_Adyacencia = vector<vector<int>>(n,vector<int>(n,0));
}

void Graph::print(){
      cout <<"~~~~~~~~~~~~~~~~~~~~inicio matriz de adyacencia~~~~~~~~~~~~~~~~~~~~" << endl;
      for(int i=0;i<Matriz_Adyacencia.size();i++){
           for(int j=0;j<Matriz_Adyacencia[i].size();j++){
               cout << Matriz_Adyacencia[i][j]<<" ";
           }
           cout << endl;
      }
      cout << "~~~~~~~~~~~~~~~~~~~~final matriz de adyacencia~~~~~~~~~~~~~~~~~~~~" << endl;
}

void Graph::agregar_arista(int peso, int n, int m){
  //cout<<n<<" "<<m<<endl;
  if(n>Matriz_Adyacencia.size() || m>Matriz_Adyacencia[0].size()){
    cout<<"fuera de alcance "<< n<<","<<m<<endl;
    cout<<Matriz_Adyacencia.size()<<" tr "<<Matriz_Adyacencia[0].size()<<endl;
    return;
  }
  //  cout<<n<<" "<<m<<endl;
    Matriz_Adyacencia[n][m] = peso;
    Matriz_Adyacencia[m][n] = peso;
};

void Graph::mapa_adyacencia(){
    int n = 4;//Matriz_Adyacencia.size();
    int m = 4;//Matriz_Adyacencia[0].size();
    int MT[4][4] = {
        {1,1,1,1},
        {1,1,0,1},
        {1,0,1,1},
        {1,1,0,1}
    };
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){

            for(int x = -1;x<2;x++){
                for(int y = -1;y<2;y++){

                    if(x==0 && y==0)continue;

                    if((i+x>-1 && i+x<n) && (j+y>-1  && j+y<m)){
                        if(MT[i][j]==1 && MT[i+x][j+y]==1){
                            agregar_arista(1,(i*4)+j,((i+x)*4)+y+j);
                        }
                   }

                }

            }
        }
    }
};

void Graph::adyacencia_mapa(){
    int Matriz_Mapa[filas][columnas] = {{0,0,0,0},
                                       {0,0,0,0},
                                       {0,0,0,0},
                                       {0,0,0,0}};
    for(int i = 0; i < filas*columnas; i++){
      for(int j = 0; j < filas*columnas; j++){
        if(Matriz_Adyacencia[i][j] == 1){
            cout<<i<<","<<j << " -> "<< i/filas<<" "<<i%columnas<<endl;
            Matriz_Mapa[i/filas][i%columnas] = 1;
        }else if(Matriz_Adyacencia[i][j] == 2){
            Matriz_Mapa[i/filas][i%columnas] = 00;
        }

      }
    }
    for(int i = 0; i < filas; i++){
      for(int j = 0; j < columnas; j++){
        cout<<Matriz_Mapa[i][j]<<" ";
      }
      cout<<endl;
    }
};