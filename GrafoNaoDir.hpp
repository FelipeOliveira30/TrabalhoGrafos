#pragma once

#include "Aresta.hpp"
#include "Grafo.hpp"

class GrafoNaoDir : public Grafo {
    public:
        GrafoNaoDir();
        ~GrafoNaoDir();
        int VerificaEuleriano();
        void AdicionaAresta(int id, int u, int v, int peso);
        void CFC();
        void OrdemTopologica();
        void FluxoMaximo();
        void FechoTransitivo();
};