#pragma once

#include "Aresta.hpp"
#include "Grafo.hpp"

class GrafoNaoDir : public Grafo {
    public:
        GrafoNaoDir(int n);
        int VerificaEuleriano();
        void AGM();
        void AdicionaAresta(int id, int u, int v, int peso);
        void CaminhoMinimo();
        int VerificaConexidade();
};
