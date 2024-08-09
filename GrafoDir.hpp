#ifndef GRAFODIR_HPP
#define GRAFODIR_HPP

#include "Aresta.hpp"
#include "Grafo.hpp"

class GrafoDir : public Grafo {
    public:
        GrafoDir();
        ~GrafoDir();
        void AVM();
        void CaminhoMinimo();
};

#endif