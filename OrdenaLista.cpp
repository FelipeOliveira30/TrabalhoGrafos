#include <string>
#include <vector>
#include <algorithm>
#include "Grafo.hpp"

void Grafo::OrdenaLista(){
    for(int i{0}; i < qtdVertices; i++){
        sort(listaAdj[i].begin(), listaAdj[i].end());
    }
}