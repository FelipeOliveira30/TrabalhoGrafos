#include <iostream>
#include <stack>
#include <vector>
#include <string>
#include "GrafoDir.hpp"

void GrafoDir::OrdemTopologica(){
    enum cores {BRANCO, CINZA, PRETO};
    cores coloracao[qtdVertices];
    for(int i = 1; i < qtdVertices; i++){
        coloracao[i] = BRANCO;
    }
    std::stack<int> pilha;
    std::stack<int> vertices;
    pilha.push(0);
    coloracao[0] = CINZA;
    int vertices_pretos{0};
    int atual = pilha.top();
    bool achou = false;
    while(vertices_pretos < qtdVertices){
        while(!pilha.empty()){
            bool achou = false;
            int atual = pilha.top();
            int i = 0;
            while(achou != true && i < listaAdj[atual].size()){
                Aresta a = listaAdj[atual][i];
                if(coloracao[a.v_entrada] == BRANCO){
                    coloracao[a.v_entrada] = CINZA;
                    pilha.push(a.v_entrada);
                    achou = true;
                }
                i++;
            }
            if(achou == false){
                pilha.pop();
                coloracao[atual] = PRETO;
                vertices_pretos++;
                vertices.push(atual);
            }
        }
        bool achouBranco = false;
        int i{0};
        while(achouBranco == false and i < qtdVertices){
            if(coloracao[i] == BRANCO){
                achouBranco = true;
                coloracao[i] = CINZA;
                vertices.push(i);
            }
            i++;
        }
    }
    while(!vertices.empty()){
        int a = vertices.top();
        std::cout << a << " ";
        vertices.pop();
    }
    std::cout << std::endl;
}
