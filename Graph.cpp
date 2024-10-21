//
// Created by gbb on 28/09/24.
//

#include "Graph.h"
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <queue>
#include <iostream>     // Para imprimir en consola con std::cout
#include <vector>       // Para utilizar std::vector en la representación de la matriz de adyacencia
#include <climits>      // Para usar INT_MAX (valor máximo de un entero)
#include <unordered_set> // Para almacenar nodos visitados en el algoritmo A*
#include <algorithm>
#include <unordered_map> // Para guardar padres y costos en A* y Dijkstra




using namespace std;

Graph::Graph(int x, int y){
  filas = x;
  columnas = y;
  srand(time(NULL));

  int n = x*y;
    Matriz_Adyacencia = vector<vector<int>>(n,vector<int>(n,0));
}




void Graph::mapa_adyacencia(vector<vector<int>>& mapa){
   // int MT[filas][columnas] = {
   //     {1,1,1,1,1},
   //     {1,1,1,1,1},
   //     {1,1,0,1,1},
   //     {1,1,0,1,1},
   //     {1,1,0,1,1},
   // };
    for(int i=0;i<filas;i++){
        for(int j=0;j<columnas;j++){

            for(int x = -1;x<2;x++){
                for(int y = -1;y<2;y++){

                    if(x==0 && y==0)continue;

                    if((i+x>-1 && i+x<filas) && (j+y>-1  && j+y<columnas)){
                        if(mapa[i][j]==1 && mapa[i+x][j+y]==1){
                            cout<<(i*filas)+j<<","<<((i+x)*filas)+y+j<<endl;
                            agregar_arista(1,(i*filas)+j,((i+x)*filas)+y+j);
                        }
                   }
                }
            }
        }
    }
};





void Graph::adyacencia_mapa(){
  int Matriz_Mapa[filas][columnas] = {{0,0,0,0,0},
                                     {0,0,0,0,0},
                                     {0,0,0,0,0},
                                     {0,0,0,0,0},
                                     {0,0,0,0,0}};
  for(int i = 0; i < filas*columnas; i++){
    for(int j = 0; j < filas*columnas; j++){
      if(Matriz_Adyacencia[i][j] == 1){
        //cout<<i<<","<<j << " -> "<< i/filas<<" "<<i%columnas<<endl;
        Matriz_Mapa[i/filas][i%columnas] = 1;
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

string Graph::Linea_Vista_bala(coords in, coords out, bool c) {
    string path = "";
    coords last;
    coords act = in;



}

string Graph::Linea_Vista_tanque(coords in, coords out, bool c) {
    std::string path = "";
    bool crashed  = c;
    int contador = 0; // Para evitar bucles infinitos

    while (in.i != out.i || in.j != out.j) { // Asegura que continúe si las coordenadas no son las finales
        if (in.i > out.i) { // El tanque tiene que moverse hacia la izquierda
            if (Matriz_Adyacencia[in.i * filas + in.j][(in.i - 1) * filas + in.j] == 1) { // Verifica si no hay obstáculo a la izquierda

                in.i--; // Se actualizan las coordenadas del tanque
                path.append("U"); // Se agrega una dirección a la ruta
            }else {
                if(!crashed){
                    //int randI , randJ;
                    //do{
                    int randI = 0;//(rand() % 3);
                    int randJ = (rand() % 2) - 1;
                    //}while(in.i+randI<0 || in.i+randI<filas || in.j+randJ<0 || in.j+randJ>columnas);
                    int tempI = in.i + randI; int tempJ = in.j + randJ;
                    coords tempOUT = coords(tempI,tempJ);
                    path.append(Linea_Vista_tanque(in,tempOUT,true));
                    crashed = true;
                }else{
                    return path;
                }
            }
        } else if (in.i < out.i) { // El tanque tiene que moverse hacia la derecha
            if (Matriz_Adyacencia[in.i * filas + in.j][(in.i + 1) * filas + in.j] == 1) { // Verifica si no hay un obstáculo a la derecha
                in.i++; // Se actualizan las coordenadas del tanque
                path.append("D"); // Se agrega una dirección a la ruta
            }else {
                if(!crashed){

                   // int randI , randJ;
                    //do{
                    int randI = 0;//-(rand() % 3);
                    int randJ = (rand() % 2) - 1;
                    //}while(in.i+randI<0 || in.i+randI<filas || in.j+randJ<0 || in.j+randJ>columnas);
                    int tempI = in.i + randI; int tempJ = in.j + randJ;
                    coords tempOUT = coords(tempI,tempJ);
                    path.append(Linea_Vista_tanque(in,tempOUT,true));
                    crashed = true;
                }else{
                    return path;
                }
            }
        }
        if (in.j > out.j) { // El tanque está por encima de las coordenadas deseadas
            if (Matriz_Adyacencia[in.i * filas + in.j][in.i * filas + (in.j - 1)] == 1) { // Verifica que exista camino hacia abajo
                in.j--; // Se actualizan las coordenadas del tanque
                path.append("L"); // Se agrega una dirección a la ruta
            }else {
                if(!crashed){
                  //  int randI , randJ;
                  //  do{
                    int randI = (rand() % 2) - 1;
                    int randJ = 0;//(rand() % 3);
                  //  }while(in.i+randI<0 || in.i+randI<filas || in.j+randJ<0 || in.j+randJ>columnas);
                    int tempI = in.i + randI; int tempJ = in.j + randJ;
                    coords tempOUT = coords(tempI,tempJ);
                    path.append(Linea_Vista_tanque(in,tempOUT,true));
                    crashed = true;
                }else{
                    return path;
                }
            }
        } else if (in.j < out.j) {
            if (Matriz_Adyacencia[in.i * filas + in.j][in.i * filas + (in.j + 1)] == 1) {
                in.j++; // Se actualizan las coordenadas del tanque
                path.append("R"); // Se agrega una dirección a la ruta
            }else {
                if(!crashed){
                    //int randI , randJ;
                  //  do{
                    int randI = (rand() % 2) - 1;
                    int randJ = 0;//-(rand() % 2);
                   // }while(in.i+randI<0 || in.i+randI<filas || in.j+randJ<0 || in.j+randJ>columnas);
                    int tempI = in.i + randI;
                    int tempJ = in.j + randJ;
                    coords tempOUT = coords(1,2);
                    path.append(Linea_Vista_tanque(in,tempOUT,true));
                    crashed = true;
                }else{
                    return path;
                }
            }
        }

        if (contador++ == 2 * (filas + columnas)) {
            return path;
        }
    }
    return path;
}
string Graph::Dijkstra(coords inicio, coords objetivo) {
    int src = inicio.i * columnas + inicio.j;  // Convertir coordenadas de inicio a índice
    int goal = objetivo.i * columnas + objetivo.j;  // Convertir destino a índice
    int n = filas * columnas;

    // Inicialización de vectores
    vector<int> dist(n, INT_MAX);
    vector<int> prev(n, -1);
    vector<bool> visitado(n, false);
    dist[src] = 0;

    // Cola de prioridad para seleccionar el nodo con menor distancia
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, src});

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        if (visitado[u]) continue;
        visitado[u] = true;

        if (u == goal) break;  // Si llegamos al destino, paramos

        // Expandimos los vecinos
        for (int v = 0; v < n; ++v) {
            if (Matriz_Adyacencia[u][v] == 1 && !visitado[v]) {
                int newDist = dist[u] + Matriz_Adyacencia[u][v];
                if (newDist < dist[v]) {
                    dist[v] = newDist;
                    prev[v] = u;  // Guardamos el nodo anterior
                    pq.push({dist[v], v});
                }
            }
        }
    }

    // Si no se encontró un camino, devolver una cadena vacía
    if (dist[goal] == INT_MAX) {
        return "";  // No hay camino disponible
    }

    // Construir el camino en direcciones
    string path = "";
    int current = goal;

    while (current != src) {
        int prev_node = prev[current];
        if (prev_node == -1) return "";  // Verificamos si hay un camino válido

        int x1 = prev_node / columnas, y1 = prev_node % columnas;
        int x2 = current / columnas, y2 = current % columnas;

        if (y1 < y2) {
            if(x1 == x2) {
                path += "R"; // Right
            }else if(x1 < x2){
                path += "b"; //diagonal abajo derecha
            }else if(x1 > x2) {
                path += "A"; //diagonal arriba derecha
            }

        }else if (y1 > y2) {
            if(x1 == x2) {
                path += "L"; // Left
            }else if(x1 < x2) {
                path += "B"; //diagnoal abajo izquierda
            }else if(x1 > x2) {
                path += "a"; //diagonal arriba izquierda
            }
        }else if (x1 < x2) path += "D";  // Down
        else if (x1 > x2) path += "U";  // Up


        current = prev_node;
    }

    reverse(path.begin(), path.end());  // Revertimos el string para tenerlo en el orden correcto
    return path;
}
