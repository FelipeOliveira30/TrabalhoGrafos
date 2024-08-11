#include <queue>
#include <vector>
#include <string>
#include "GrafoDir.hpp"

int GrafoDir::VerificaBipartido(){
    enum cores {BRANCO, AZUL, VERMELHO};
    cores coloracao[qtdVertices];
    for(int i = 1; i < qtdVertices; i++){
        coloracao[i] = BRANCO;
    }
    int vertices_coloridos{0};
    std::queue<int> fila;
    fila.push(0);
    coloracao[0] = AZUL;
    while(vertices_coloridos < qtdVertices){
        while(!fila.empty()){
            int atual = fila.front();
            fila.pop();
            for(int i = 0; i < listaAdj[atual].size(); i++){
                Aresta a = listaAdj[atual][i];
                if(coloracao[a.v_entrada] == BRANCO){
                    if(coloracao[atual] == AZUL)
                        coloracao[a.v_entrada] = VERMELHO;
                    else
                        coloracao[a.v_entrada] = AZUL;
                    fila.push(a.v_entrada);
                }
                else if(coloracao[a.v_entrada] == coloracao[atual])
                    return 0;
            }
        }
        int i = 0;
        bool achou = false;
        while(i < qtdVertices && achou == false){
            if(coloracao[i] == BRANCO){
                coloracao[i] = AZUL;
                fila.push(i);
                achou = true;
            }
        i++;
        }
    }
    return 1;
}
