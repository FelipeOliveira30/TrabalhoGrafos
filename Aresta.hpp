#pragma once

struct Aresta {
    int v_entrada;
    int peso;
    int id;

    bool operator<(const Aresta& outra) {
        return this->v_entrada < outra.v_entrada;
    }
};
