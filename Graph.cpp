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




void Graph::mapa_adyacencia(){
    int MT[filas][columnas] = {
        {1,1,1,1,1},
        {1,1,1,1,1},
        {1,1,0,1,1},
        {1,1,1,1,1},
        {1,1,1,1,1},
    };
    for(int i=0;i<filas;i++){
        for(int j=0;j<columnas;j++){

            for(int x = -1;x<2;x++){
                for(int y = -1;y<2;y++){

                    if(x==0 && y==0)continue;

                    if((i+x>-1 && i+x<filas) && (j+y>-1  && j+y<columnas)){
                        if(MT[i][j]==1 && MT[i+x][j+y]==1){
                            cout<<(i*filas)+j<<","<<((i+x)*filas)+y+j<<endl;
                            agregar_arista(1,(i*filas)+j,((i+x)*filas)+y+j);
                        }
                   }
                }
            }
        }
    }
};



string Graph::Linea_Vista_aux(coords in, coords out, bool c) {
    cout<<out.i<<" "<<out.j<<" "<<in.i<<" "<<in.j<<endl;
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
                    int randI , randJ;
                    do{
                    int randI = (rand() % 3);
                    int randJ = (rand() % 5) - 2;
                    }while(in.i+randI<0 || in.i+randI<filas || in.j+randJ<0 || in.j+randJ>columnas);
                    int tempI = in.i + randI; int tempJ = in.j + randJ;
                    coords tempOUT = coords(tempI,tempJ);
                    path.append(Linea_Vista_aux(in,tempOUT,true));
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

                    int randI , randJ;
                    do{
                    int randI = -(rand() % 3);
                    int randJ = (rand() % 5) - 2;
                    }while(in.i+randI<0 || in.i+randI<filas || in.j+randJ<0 || in.j+randJ>columnas);
                    int tempI = in.i + randI; int tempJ = in.j + randJ;
                    coords tempOUT = coords(tempI,tempJ);
                    path.append(Linea_Vista_aux(in,tempOUT,true));
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
                    int randI , randJ;
                    do{
                    int randI = (rand() % 5) - 2;
                    int randJ = (rand() % 3);
                    }while(in.i+randI<0 || in.i+randI<filas || in.j+randJ<0 || in.j+randJ>columnas);
                    int tempI = in.i + randI; int tempJ = in.j + randJ;
                    coords tempOUT = coords(tempI,tempJ);
                    path.append(Linea_Vista_aux(in,tempOUT,true));
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
                    int randI , randJ;
                    do{
                    int randI = (rand() % 5) - 2;
                    int randJ = -(rand() % 3);
                    }while(in.i+randI<0 || in.i+randI<filas || in.j+randJ<0 || in.j+randJ>columnas);
                    int tempI = in.i + randI; int tempJ = in.j + randJ;
                    coords tempOUT = coords(tempI,tempJ);
                    path.append(Linea_Vista_aux(in,tempOUT,true));
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

/*
string Graph::Linea_Vista(coords in, coords out,bool chocado){
    std::string path = "";
    //int x1 = in.i;int y1 = in.j;//se obitienen las cordenas del punto de inicio
    //int x2 = out.i;int y2 = out.j;//se obtienen las cordenadas finales
    int contador = 0;//esta para evitar bocles infinitos

    while(in.i!=out.i || in.j!=out.j){//se asegura que continue si las coordenadas no son las finales

        if(in.i>out.i){//el tanque tiene que moverse para la izquierda
          if((Matriz_Adyacencia[in.i * filas + in.j][(in.i-1)*filas+in.j])==1){//se verifica si no hay obstaculo a la izquierda
            in.i--;//se actualiza las coordenadas del tanque
            path.append("U");//se agrega una direccion a la ruta
          }else{
             if(!chocado){//si es la primera ves que se encuentra un obstaculo
                coords tempIN = {x1,y1};
                int x[2];//sub cordenadas finales aleatorias
                x[0] = x1 + rand()%2-2;//genera un valor de -5 a 5 para las nuevas coordenadas aleatorias
                x[1] = y1 + (2 - abs(x[0])) * (rand()%2 == 0 ? 1:-1);//genera el complemento de la primera coordenada para no exeder un radio constante
                cout << tempIN[0] <<"int"<<tempIN[1]<<" "<<x[0]<<"out"<<x[1]<<endl;
                int tempout[2] = {1,4};
                path.append(Linea_Vista(tempIN,tempout,true));//genera una llamada recursiva para obtener la direccion a la posicion aleatoria
                chocado = true;//se asegura que no continue si vuelve a llegar a un obstaculo
             }else{//al haber un obstaculo por segunda ves se retorna el camino hasta el momento
               return path;
             }
          }

        }else if(x1<x2){//el tanque tiene que moverse para la derecha
          if(Matriz_Adyacencia[x1 * filas + y1][(x1+1)*columnas+y1]==1){//verifica que no hay un obstaculo a la derecha
            x1++;//actualiza las coordenadas del tanque
            path.append("D");//se agrega una direccion a la ruta
          }else{
            if(!chocado){//se asegura que sea el primer obstaculo que el tanque encuentra
              int tempIN[2] = { x1,y1};
              int x[2];//instancia de las coordenadas subfinales
              x[0] = x1 + rand()%2-2;//calcula el primer valor de las coordenadas del movimeinto aleatorio
              x[1] = y1 + (2 - abs(x[0])) * (rand()%2 == 0 ? 1:-1);//calcula el complemento de la coordenanda para maneterner un radio constante
              cout << tempIN[0] <<"int"<<tempIN[1]<<" "<<x[0]<<"out"<<x[1]<<endl;
              int tempout[2] = {1,3};
              path.append(Linea_Vista(tempIN,tempout,true));//realiza una llamada recursiva para calcular la ruta al punto aleatorio
              chocado = true;//se cerciora que no continue si vuleve a chocar
            }else{//el segundo obstaculo encontrado genera que se retorne el path
              return path;
            }
          }
        }
        if(y1>y2){//el tanque esta por encima de las coordenadas deceadas
          if(Matriz_Adyacencia[x1*filas+y1][x1*columnas+(y1-1)]==1){//se verifica que exista camino hacia abajo
            y1--;//se actualizan las coordenas del tanque
            path.append("L");//se agrega una direccion a la ruta
          }else{
            if(!chocado){
              int tempIN[2] = { x1,y1};
              int x[2];
              x[0] = x1 + rand()%2-2;
              x[1] = y1 + (2 - abs(x[0])) * (rand()%2 == 0 ? 1:-1);
              cout << tempIN[0] <<"int"<<tempIN[1]<<" "<<x[0]<<"out"<<x[1]<<endl;
              path.append(Linea_Vista(tempIN,x,true));
              return path;
            }else{
              return path;
            }
          }

        }else if(y1<y2){
          if(Matriz_Adyacencia[x1*filas+y1][x1*columnas+(y1+1)]==1){
            y1++;
            path.append("R");
          }else{
              int tempIN[2] = {x1,y1};
              int x[2];
              x[0] = x1 + rand()%2-2;
              x[1] = y1 + (2 - abs(x[0])) * (rand()%2 == 0 ? 1:-1);
              cout << tempIN[0] <<"int"<<tempIN[1]<<" "<<x[0]<<"out"<<x[1]<<endl;
              path.append(Linea_Vista(tempIN,x,true));
              return path;
          }
        }
        if(contador++ == 2*(filas+columnas)){
            return path;
        }
        //cout<<x1<<" - "<<y1<<endl;
    }
    return path;
};

string Graph::Linea_Vista_aux(coords in,coords out){
    std::string path = "";

    int contador = 0;//esta para evitar bocles infinitos

    while(x1!=x2 || y1!=y2){//se asegura que continue si las coordenadas no son las finales

        if(x1>x2){//el tanque tiene que moverse para la izquierda
          cout<<x1*filas+y1<<"~"<<(x1-1)*filas+y1<<endl;
          if(Matriz_Adyacencia[x1*filas+y1][(x1-1)*filas+y1]==1){//se verifica si no hay obstaculo a la izquierda
            x1--;//se actualiza las coordenadas del tanque
            path.append("U");//se agrega una direccion a la ruta
          }
        }else if(x1<x2){//el tanque tiene que moverse para la derecha
          cout<<x1*filas+y1<<"~"<<(x1+1)*filas+y1<<endl;
          if(Matriz_Adyacencia[x1*filas+y1][(x1+1)*filas+y1]==1){//verifica que no hay un obstaculo a la derecha
            x1++;//actualiza las coordenadas del tanque
            path.append("D");//se agrega una direccion a la ruta
          }
        }
        if(y1>y2){//el tanque esta por encima de las coordenadas deceadas
          cout<<x1*filas+y1<<"~"<<(x1)*filas+y1-1<<endl;
          if(Matriz_Adyacencia[x1*filas+y1][x1*filas+(y1-1)]==1){//se verifica que exista camino hacia abajo
            y1--;//se actualizan las coordenas del tanque
            path.append("L");//se agrega una direccion a la ruta
          }
        }else if(y1<y2){
          cout<<x1*filas+y1<<"~"<<(x1-1)*filas+y1+1<<endl;
          if(Matriz_Adyacencia[x1*filas+y1][x1*filas+(y1+1)]==1){
            y1++;
            path.append("R");
          }
        }
        if(contador++ == 2*(filas+columnas)){
            return path;
        }
        //cout<<path<<endl;
    }
    return path;
}
*/