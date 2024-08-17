#include <iostream>
#include <stack>
#include <algorithm>
#include <string>
#include <vector>
#include "GrafoDir.hpp"

void GrafoDir::FechoTransitivo(){
    std::vector<std::string> verticesAlcancaveis;

    enum cores {BRANCO, CINZA, PRETO};
    cores coloracao[qtdVertices];
    for(int i = 1; i < qtdVertices; i++){
        coloracao[i] = BRANCO;
    }
    std::stack<int> pilha;
    pilha.push(0);
    coloracao[0] = CINZA;
    while(!pilha.empty()){
        int atual = pilha.top();
        bool achou = false;
        int i = 0;
        while(achou != true && i < listaAdj[atual].size()){
            Aresta a = listaAdj[atual][i];
            if(coloracao[a.v_entrada] == BRANCO){
                coloracao[a.v_entrada] = CINZA;
                pilha.push(a.v_entrada);
                achou = true;
                verticesAlcancaveis.push_back(std::to_string(a.v_entrada));
            }
            i++;
        }
        if(achou == false){
            pilha.pop();
            coloracao[atual] = PRETO;
        }
    }

    sort(verticesAlcancaveis.begin(), verticesAlcancaveis.end());
    for(int i = 0; i < verticesAlcancaveis.size(); i++){
        std::cout << verticesAlcancaveis[i] << " ";
    }
    std::cout << std::endl;
} 