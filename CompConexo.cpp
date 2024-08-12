#include <iostream>
#include <vector>
#include <queue>
#include "GrafoNaoDir.hpp"
#include "GrafoDir.hpp"

int GrafoDir::ComponentesFortementeConexas(){
    enum cores {BRANCO, CINZA, PRETO};
    cores coloracao[qtdVertices];
    for(int i = 1; i < qtdVertices; i++){
        coloracao[i] = BRANCO;
    }
    std::queue<int> fila;
    fila.push(0);
    coloracao[0] = CINZA;
    int num_componentes{1};
    int v_pretos{0};
    while(v_pretos < qtdVertices){
        while(!fila.empty()){
            int atual = fila.front();
            fila.pop();
            for(int i = 0; i < listaAdj[atual].size(); i++){
                Aresta a = listaAdj[atual][i];
                if(coloracao[a.v_entrada] == BRANCO){
                    coloracao[a.v_entrada] = CINZA;
                    fila.push(a.v_entrada);
                }
            }
            coloracao[atual] = PRETO;
            v_pretos++;
        }
        bool achou = false;
        int i{0};
        while(achou == false and i < qtdVertices){
            if(coloracao[i] == BRANCO){
                num_componentes++;
                achou = true;
                coloracao[i] = CINZA;
                fila.push(i);
            }
            i++;
        }
    }
    return num_componentes;
}


int GrafoNaoDir::ComponentesConexas(){
    enum cores {BRANCO, CINZA, PRETO};
    cores coloracao[qtdVertices];
    for(int i = 1; i < qtdVertices; i++){
        coloracao[i] = BRANCO;
    }
    std::queue<int> fila;
    fila.push(0);
    coloracao[0] = CINZA;
    int num_componentes{1};
    int v_pretos{0};
    while(v_pretos < qtdVertices){
        while(!fila.empty()){
            int atual = fila.front();
            fila.pop();
            for(int i = 0; i < listaAdj[atual].size(); i++){
                Aresta a = listaAdj[atual][i];
                if(coloracao[a.v_entrada] == BRANCO){
                    coloracao[a.v_entrada] = CINZA;
                    fila.push(a.v_entrada);
                }
            }
            coloracao[atual] = PRETO;
            v_pretos++;
        }
        bool achou = false;
        int i{0};
        while(achou == false and i < qtdVertices){
            if(coloracao[i] == BRANCO){
                num_componentes++;
                achou = true;
                coloracao[i] = CINZA;
                fila.push(i);
            }
            i++;
        }
    }
    return num_componentes;
}

