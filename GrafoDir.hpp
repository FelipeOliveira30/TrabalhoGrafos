#pragma once

#include "Aresta.hpp"
#include "Grafo.hpp"

class GrafoDir : public Grafo {
    public:
        GrafoDir();
        ~GrafoDir();
        void AGM();
        void AdicionaAresta(int id, int u, int v, int peso);
        int VerificaEuleriano();
        void CaminhoMinimo();
};
