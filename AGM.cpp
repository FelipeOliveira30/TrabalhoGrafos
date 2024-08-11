#include <iostream>
#include <stack>
#include <algorithm>
#include <queue>
#include <vector>
#include <string>
#include "GrafoDir.hpp"
#include "GrafoNaoDir.hpp"
#include "GrafoDir.hpp"
#include "DisjointSet.hpp"

void GrafoNaoDir::AGM(){
    std::vector<OrdAresta> arestas_ord;
    int nArestas{0};
    OrdAresta arestaO;
    for(int i{0}; i < qtdVertices; i++){
        for(int j{0}; j < listaAdj[i].size(); j++){
            arestaO.v_saida = i;
            arestaO.aresta.id = listaAdj[i][j].id;
            arestaO.aresta.peso = listaAdj[i][j].peso;
            arestaO.aresta.v_entrada = listaAdj[i][j].v_entrada;
            arestas_ord.push_back(arestaO);
            nArestas++;
        }
    }
    std::sort(arestas_ord.begin(), arestas_ord.end(), [](const OrdAresta& a, const OrdAresta& b) {
        return a.aresta.peso < b.aresta.peso;
    });
    int soma{0};
    DisjointSet conj(qtdVertices);  
    for(int i{0}; i < nArestas; i++){
        int v = arestas_ord[i].v_saida;
        int u = arestas_ord[i].aresta.v_entrada; 
        if(conj.encontraSet(v) != conj.encontraSet(u)){
            soma += arestas_ord[i].aresta.peso;
            conj.une(v, u);
        }
    }
    std::cout << soma << std::endl;
}
