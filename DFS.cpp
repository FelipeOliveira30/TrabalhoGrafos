#include <iostream>
#include <stack>
#include <vector>
#include <string>
#include "Grafo.hpp"

int* Grafo::DFS(){
    enum cores {BRANCO, CINZA, PRETO};
    int* pais = new int[qtdVertices];
    for(int i{0}; i < qtdVertices; i++)
        pais[i] = i;
    cores coloracao[qtdVertices];
    for(int i = 1; i < qtdVertices; i++){
        coloracao[i] = BRANCO;
    }
    std::stack<int> pilha;
    pilha.push(0);
    coloracao[0] = CINZA;
    int atual = pilha.top();
    bool achou = false;
    while(!pilha.empty()){
        bool achou = false;
        int atual = pilha.top();
        int i = 0;
        while(achou != true && i < listaAdj[atual].size()){
            Aresta a = listaAdj[atual][i];
            if(coloracao[a.v_entrada] == BRANCO){
                coloracao[a.v_entrada] = CINZA;
                pilha.push(a.v_entrada);
                achou = true;
            }
            pais[a.v_entrada] = atual;
            i++;
        }
        if(achou == false){
            pilha.pop();
            coloracao[atual] = PRETO;
        }
    }
    return pais;
}



void Grafo::Exibe_DFS(){
    enum cores {BRANCO, CINZA, PRETO};
    cores coloracao[qtdVertices];
    for(int i = 1; i < qtdVertices; i++){
        coloracao[i] = BRANCO;
    }
    std::stack<int> pilha;
    pilha.push(0);
    coloracao[0] = CINZA;
    while(!pilha.empty()){
        int atual = pilha.top();
        bool achou = false;
        int i = 0;
        while(achou != true && i < listaAdj[atual].size()){
            Aresta a = listaAdj[atual][i];
            if(coloracao[a.v_entrada] == BRANCO){
                coloracao[a.v_entrada] = CINZA;
                pilha.push(a.v_entrada);
                achou = true;
                std::cout << a.id << " ";
            }
            i++;
        }
        if(achou == false){
            pilha.pop();
            coloracao[atual] = PRETO;
        }
    }
}