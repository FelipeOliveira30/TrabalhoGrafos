#include <algorithm>
#include <vector>
#include <string>
#include "GrafoDir.hpp"
#include "GrafoNaoDir.hpp"

int GrafoDir::VerificaEuleriano(){
    int* pais = new int[qtdVertices];
    for(int i{1}; i < qtdVertices; i++){
        if(pais[i] == i)
            return 0;
    }
    int matriz_vertices[qtdVertices][2];
    for(int i{0}; i < qtdVertices; i++){
        matriz_vertices[i][0] = listaAdj[i].size();
        matriz_vertices[i][1] = 0;
    }
    for(int i{0}; i < qtdVertices; i++){
        for(int j{0}; j < listaAdj[i].size(); j++){
            matriz_vertices[listaAdj[i][j].v_entrada][1]++;
        }
    }
    for(int i{0}; i < qtdVertices; i++){
        if(matriz_vertices[i][0] != matriz_vertices[i][1])
            return 0;
    }
    return 1;
}

void GrafoNaoDir::AdicionaAresta(int id, int u, int v, int peso){
    Aresta aresta;
    aresta.id = id;
    aresta.v_entrada = v;
    aresta.peso = peso;
    listaAdj[u].push_back(aresta);
    std::sort(listaAdj[u].begin(), listaAdj[u].end());
    aresta.v_entrada = u;
    listaAdj[v].push_back(aresta);
    std::sort(listaAdj[u].begin(), listaAdj[u].end());
}