#include <iostream>
#include <queue>
#include "GrafoNaoDir.hpp"

int GrafoNaoDir:: ComponentesConexas(){
    int num_componentes = 0;
    enum cores {BRANCO, CINZA, PRETO};

    int* pais = new int[qtdVertices];
    for(int i{0}; i < qtdVertices; i++)
        pais[i] = i;
    
    cores coloracao[qtdVertices];
    for(int i = 1; i < qtdVertices; i++){
        coloracao[i] = BRANCO;
    }

    for(int i{0}; i < qtdVertices; i++){
        if(coloracao[i] == BRANCO){
            num_componentes++;
            std::queue<int> fila;
            fila.push(i);
            coloracao[i] = CINZA;

            
            while(!fila.empty()){
                int atual = fila.front();
                fila.pop();
                for(int j = 0; j < listaAdj[atual].size(); j++){
                    Aresta a = listaAdj[atual][j];
                    if(coloracao[a.v_entrada] == BRANCO){
                        coloracao[a.v_entrada] = CINZA;
                        fila.push(a.v_entrada);
                        pais[a.v_entrada] = atual;
                    }
                }
                coloracao[atual] = PRETO;
                
            }
        }
    }

    delete [] pais;

    return num_componentes;
}