#include <vector>
#include <string>
#include "GrafoDir.hpp"
#include "GrafoNaoDir.hpp"

int GrafoNaoDir::VerificaConexidade(){
    int* pais = new int[qtdVertices];
    pais = BFS();
    for(int i{1}; i < qtdVertices; i++){
        if(pais[i]==i)
            return 1;
    }
    delete[] pais;
    return 0;
}

int GrafoDir::VerificaConexidade(){
    GrafoNaoDir grafo_aux(qtdVertices);
    for(int i{0}; i < qtdVertices; i++){
        for(int j{0}; j < listaAdj[i].size(); j++){
            int id = listaAdj[i][j].id;
            int v = listaAdj[i][j].v_entrada;
            int u = i;
            int peso = 1;
            grafo_aux.AdicionaAresta(id, v, u, 1);
        }
    }
    return grafo_aux.VerificaConexidade();
}