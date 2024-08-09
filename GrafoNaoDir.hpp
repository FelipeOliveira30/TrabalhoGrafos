#ifndef GRAFNAOODIR_HPP
#define GRAFNAOODIR_HPP

#include "Aresta.hpp"
#include "Grafo.hpp"

class GrafoNaoDir : public Grafo {
    public:
        GrafoNaoDir();
        ~GrafoNaoDir();
        void CFC();
        void OrdemTopologica();
        void FluxoMaximo();
        void FechoTransitivo();
};

#endif