#pragma once

#include "Aresta.hpp"
#include <vector>

class Grafo {
protected:
    std::vector<Aresta>* listaAdj;
    int qtdVertices;
public:
    Grafo(int n);
    ~Grafo();
    std::vector<int> BFS();
    std::vector<int> DFS();
    void ComponentesConexas();
    void TrilhaEuleriana();
    void ArestasPonte();
    void VerticesArticulacao();
    int VerificaConexidade();
    int VerificaBipartido();
    int VerificaCiclo(); 
};
