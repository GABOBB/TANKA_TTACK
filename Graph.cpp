//
// Created by gbb on 28/09/24.
//

#include "Graph.h"
#include <cstdlib>
#include <ctime>
#include <cmath>

using namespace std;

Graph::Graph(int x, int y){
  filas = x;
  columnas = y;
  srand(time(NULL));

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
    int MT[n][m] = {
        {1,1,1,1},
        {1,1,1,1},
        {1,0,1,1},
        {1,1,1,1}
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


string Graph::Linea_Vista(int in[2], int out[2],bool chocado){
    std::string path = "";
    int x1 = in[0];int y1 = in[1];//se obitienen las cordenas del punto de inicio
    int x2 = out[0];int y2 = out[1];//se obtienen las cordenadas finales
    int contador = 0;//esta para evitar bocles infinitos

    while(x1!=x2 || y1!=y2){//se asegura que continue si las coordenadas no son las finales

        if(x1>x2 ){//el tanque tiene que moverse para la izquierda
          if(Matriz_Adyacencia[x1*4+y1][x1*4+(y1-1)]==1){//se verifica si no hay obstaculo a la izquierda
            x1--;//se actualiza las coordenadas del tanque
            path.append("L");//se agrega una direccion a la ruta
          }else{
             if(!chocado){//si es la primera ves que se encuentra un obstaculo
                int x[2];//sub cordenadas finales aleatorias
                x[0] = x1 + rand()%2-2;//genera un valor de -5 a 5 para las nuevas coordenadas aleatorias
                x[1] = y1 + (5 - abs(x[0])) * (rand()%2 == 0 ? 1:-1);//genera el complemento de la primera coordenada para no exeder un radio constante
                path.append(Linea_Vista(in,x,true));//genera una llamada recursiva para obtener la direccion a la posicion aleatoria
                chocado = true;//se asegura que no continue si vuelve a llegar a un obstaculo
             }else{//al haber un obstaculo por segunda ves se retorna el camino hasta el momento
               return path;
             }
          }

        }else if(x1<x2){//el tanque tiene que moverse para la derecha
          if(Matriz_Adyacencia[x1*4+y1][x1*4+(y1+1)]==1){//verifica que no hay un obstaculo a la derecha
            x1++;//actualiza las coordenadas del tanque
            path.append("R");//se agrega una direccion a la ruta
          }else{
            if(!chocado){//se asegura que sea el primer obstaculo que el tanque encuentra
              int x[2];//instancia de las coordenadas subfinales
              x[0] = x1 + rand()%2-2;//calcula el primer valor de las coordenadas del movimeinto aleatorio
              x[1] = y1 + (5 - abs(x[0])) * (rand()%2 == 0 ? 1:-1);//calcula el complemento de la coordenanda para maneterner un radio constante
              path.append(Linea_Vista(in,x,true));//realiza una llamada recursiva para calcular la ruta al punto aleatorio
              chocado = true;//se cerciora que no continue si vuleve a chocar
            }else{//el segundo obstaculo encontrado genera que se retorne el path
              return path;
            }
          }
        }
        if(y1>y2){//el tanque esta por encima de las coordenadas deceadas
          if(Matriz_Adyacencia[x1*4+y1][(x1-1)*4+y1]==1){//se verifica que exista camino hacia abajo
            y1--;//se actualizan las coordenas del tanque
            path.append("D");//se agrega una direccion a la ruta
          }else{
            if(!chocado){
              int x[2];
              x[0] = x1 + rand()%2-2;
              x[1] = y1 + (5 - abs(x[0])) * (rand()%2 == 0 ? 1:-1);
              path.append(Linea_Vista(in,x,true));
              return path;
            }else{
              return path;
            }
          }

        }else if(y1<y2){
          if(Matriz_Adyacencia[x1*4+y1][(x1+1)*4+y1]==1){
            y1++;
            path.append("U");
          }else{
              int x[2];
              x[0] = x1 + rand()%2-2;
              x[1] = y1 + (5 - abs(x[0])) * (rand()%2 == 0 ? 1:-1);
              path.append(Linea_Vista(in,x,true));
              return path;
          }
        }
        if(contador++ == 2*(filas+columnas)){
            return path;
        }
        cout<<x1<<" - "<<y1<<endl;
    }
    return path;
};

string Graph::Linea_Vista_aux(int in[2]){

}