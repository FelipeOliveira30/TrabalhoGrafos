#include <vector>
#include <string>
#include "GrafoDir.hpp"
#include "GrafoNaoDir.hpp"

void GrafoDir::AdicionaAresta(int id, int u, int v, int peso){
    Aresta aresta;
    aresta.id = id;
    aresta.v_entrada = v;
    aresta.peso = peso;
    listaAdj[u].push_back(aresta);
}

void GrafoNaoDir::AdicionaAresta(int id, int u, int v, int peso){
    Aresta aresta;
    aresta.id = id;
    aresta.v_entrada = v;
    aresta.peso = peso;
    listaAdj[u].push_back(aresta);
    aresta.v_entrada = u;
    listaAdj[v].push_back(aresta);
}