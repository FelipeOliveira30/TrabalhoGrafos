#include <vector>
#include <string>
#include "Grafo.hpp"

Grafo::Grafo(int n) : qtdVertices(n) {
    listaAdj = new Lista[n];
}

Grafo::~Grafo(){
    delete[] listaAdj;
}