#ifndef GRAFO_HPP
#define GRAFO_HPP

#include "Aresta.hpp"
#include <vector>

class Grafo {
protected:
    std::vector<Aresta>* listaAdj;
    int qtdVertices;
public:
    Grafo(int n);
    ~Grafo();
    void BFS();
    void DFS();
    void ComponentesConexas();
    void TrilhaEuleriana();
    void ArestasPonte();
    void VerticesArticulacao();
    void AdicionaAresta(int id, int u, int v, int peso);
    int VerificaConexidade();
    int VerificaBipartido();
    int VerificaEuleriano();
    int VerificaCiclo(); 
};

#endif