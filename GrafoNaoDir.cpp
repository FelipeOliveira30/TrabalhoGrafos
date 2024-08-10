#include <iostream>
#include "GrafoNaoDir.hpp"
#include <vector>
#include<algorithm>

int GrafoNaoDir::VerificaEuleriano(){
    int pesos;
    int conexo = VerificaConexidade();
    if(conexo == 0)
        return 0;
    for(int i{0}; i < qtdVertices; i++){
        pesos = listaAdj[i].size();
        if(pesos%2 != 0)
            return 0;
    }
    return 1;
}