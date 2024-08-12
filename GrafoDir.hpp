#pragma once

#include "Aresta.hpp"
#include "Grafo.hpp"

class GrafoDir : public Grafo {
    public:
        GrafoDir(int n);
        void AdicionaAresta(int id, int u, int v, int peso);
        int VerificaEuleriano();
        int ComponentesFortementeConexas();
        void OrdemTopologica();
        void FluxoMaximo();
        void FechoTransitivo();
        int VerificaConexidade();
        int VerificaBipartido();
};
