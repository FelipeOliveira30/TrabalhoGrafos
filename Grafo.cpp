#include <iostream>
#include "Aresta.hpp"
#include "Grafo.hpp"
#include <queue>
#include <stack>
#include <vector>

int Grafo::VerificaBipartido(){
    enum cores {BRANCO, AZUL, VERMELHO};
    cores coloracao[qtdVertices];
    for(int i = 1; i < qtdVertices; i++){
        coloracao[i] = BRANCO;
    }
    int vertices_coloridos{0};
    std::queue<int> fila;
    fila.push(0);
    coloracao[0] = AZUL;
    while(vertices_coloridos < qtdVertices){
        while(!fila.empty()){
            int atual = fila.front();
            fila.pop();
            for(int i = 0; i < listaAdj[atual].size(); i++){
                Aresta a = listaAdj[atual][i];
                if(coloracao[a.v_entrada] == BRANCO){
                    if(coloracao[atual] == AZUL)
                        coloracao[a.v_entrada] = VERMELHO;
                    else
                        coloracao[a.v_entrada] = AZUL;
                    fila.push(a.v_entrada);
                }
                else if(coloracao[a.v_entrada] == coloracao[atual])
                    return 0;
            }
        }
        int i = 0;
        bool achou = false;
        while(i < qtdVertices && achou == false){
            if(coloracao[i] == BRANCO){
                coloracao[i] = AZUL;
                fila.push(i);
                achou = true;
            }
        i++;
        }
    }
    return 1;
}

    enum cores {BRANCO, CINZA, PRETO};
std::vector<int> Grafo::DFS(){
    std::vector<int> arvore;
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
                arvore.push_back(a.id);
            }
            i++;
        }
        if(achou == false)
            pilha.pop();
        coloracao[atual] = PRETO;
    }
    return arvore;
}

std::vector<int> Grafo::BFS(){
    enum cores {BRANCO, CINZA, PRETO};
    std::vector<int> arvore;
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
                arvore.push_back(a.id);
            }
        }
        coloracao[atual] = PRETO;
    }
    return arvore;
}

int Grafo::VerificaConexidade(){
    std::vector<int> arvore = BFS();
    if(arvore.size() == qtdVertices)
        return 1;
    return 0;
}