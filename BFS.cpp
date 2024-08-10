#include <iostream>
#include <queue>
#include <vector>
#include <string>
#include "Grafo.hpp"

int* Grafo::BFS(){
    enum cores {BRANCO, CINZA, PRETO};
    int* pais = new int[qtdVertices];
    for(int i{0}; i < qtdVertices; i++)
        pais[i] = i;
    cores coloracao[qtdVertices];
    for(int i = 1; i < qtdVertices; i++){
        coloracao[i] = BRANCO;
    }
    std::queue<int> fila;
    fila.push(0);
    coloracao[0] = CINZA;
    while(!fila.empty()){
        int atual = fila.front();
        fila.pop();
        for(int i = 0; i < listaAdj[atual].size(); i++){
            Aresta a = listaAdj[atual][i];
            if(coloracao[a.v_entrada] == BRANCO){
                coloracao[a.v_entrada] = CINZA;
                fila.push(a.v_entrada);
                pais[i] = atual;
            }
        }
        coloracao[atual] = PRETO;
    }
    return pais;
}

void Grafo::Exibe_BFS(){
    enum cores {BRANCO, CINZA, PRETO};
    cores coloracao[qtdVertices];
    for(int i = 1; i < qtdVertices; i++){
        coloracao[i] = BRANCO;
    }
    std::queue<int> fila;
    fila.push(0);
    coloracao[0] = CINZA;
    while(!fila.empty()){
        int atual = fila.front();
        fila.pop();
        for(int i = 0; i < listaAdj[atual].size(); i++){
            Aresta a = listaAdj[atual][i];
            if(coloracao[a.v_entrada] == BRANCO){
                coloracao[a.v_entrada] = CINZA;
                fila.push(a.v_entrada);
                std::cout << a.id << " ";
            }
        }
        coloracao[atual] = PRETO;
    }
}


