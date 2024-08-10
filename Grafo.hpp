#pragma once

#include "Aresta.hpp"
#include <vector>

typedef std::vector<Aresta> Lista;

class Grafo {
protected:
    Lista* listaAdj;
    int qtdVertices;
public:
    Grafo(int n);
    ~Grafo();
    void Exibe_BFS();
    void Exibe_DFS();
    int* BFS();
    int* DFS();
    void ComponentesConexas();
    void TrilhaEuleriana();
    void ArestasPonte();
    void VerticesArticulacao();
    int VerificaBipartido();
    int VerificaCiclo(); 
};
