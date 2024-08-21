#include <iostream>
#include <stack>
#include <algorithm>
#include <queue>
#include <vector>
#include <string>
#include <cstdlib>
#include <utility>
#include <limits>
#include <functional>

#define INF std::numeric_limits<int>::max()

struct Aresta {
    int v_entrada;
    int peso;
    int id;

    bool operator<(const Aresta& outra) {
        return this->v_entrada < outra.v_entrada;
    }

    bool comparaPeso(const Aresta& a, const Aresta& b){
        return a.peso < b.peso;
    }
};

struct OrdAresta{
    Aresta aresta;
    int v_saida;
};

class DisjointSet {
private:
    std::vector<int> pais; 
    std::vector<int> rank;
public:
    DisjointSet(int n);
    void une(int x, int y);
    void linka(int x, int y);
    int encontraSet(int x);
};

DisjointSet::DisjointSet(int n){
    rank.assign(n, 0);
    for(int i{0}; i < n; i++){
        pais.push_back(i);
    }
}

int DisjointSet::encontraSet(int x){
    if(x != pais[x])
        pais[x] = encontraSet(pais[x]);
    return pais[x];
}

void DisjointSet::une(int x, int y){
    linka(encontraSet(x), encontraSet(y));
}

void DisjointSet::linka(int x, int y){
    if(rank[x] > rank[y])
        pais[y] = x;
    else 
        pais[x] = y;
    if(rank[x] = rank[y])
        rank[y] = rank[y] + 1;
}

typedef std::vector<Aresta> Lista;

class Grafo {
protected:
    Lista* listaAdj;
    int qtdVertices;
public:
    Grafo(int n);
    ~Grafo();
    void Exibe_BFS();
    void Exibe_DFS();
    void Gera_BFS(char simbolo);
    void Gera_DFS(char simbolo);
    int* BFS();
    int* DFS();
    void ArestasPonte();
    void DFSPonte(int u, int disc[], int low[], bool visitado[], int pais[], int& arestasPonte, int& indiceAtual);
    void VerticesArticulacao();
    void DFSArticulacao(int u, int disc[], int low[], bool visitado[], int pais[], bool articulacao[], int& indiceAtual, int& qtdArticulacao);
    void OrdenaLista();
};

Grafo::Grafo(int n) : qtdVertices(n) {
    listaAdj = new Lista[n];
}

Grafo::~Grafo(){
    delete[] listaAdj;
}

void Grafo::Exibe_BFS(){
    enum cores {BRANCO, CINZA, PRETO};
    cores coloracao[qtdVertices];
    for(int i = 1; i < qtdVertices; i++){
        coloracao[i] = BRANCO;
    }
    std::queue<int> fila;
    fila.push(0);
    coloracao[0] = CINZA;
    while(!fila.empty()){
        int atual = fila.front();
        fila.pop();
        for(int i = 0; i < listaAdj[atual].size(); i++){
            Aresta a = listaAdj[atual][i];
            if(coloracao[a.v_entrada] == BRANCO){
                coloracao[a.v_entrada] = CINZA;
                fila.push(a.v_entrada);
                std::cout << a.id << " ";
            }
        }
        coloracao[atual] = PRETO;
    }
}

void Grafo::Exibe_DFS(){
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
                std::cout << a.id << " ";
            }
            i++;
        }
        if(achou == false){
            coloracao[atual] = PRETO;
            pilha.pop();
        }
    }
}

void Grafo::VerticesArticulacao() {
    int disc[qtdVertices];
    int low[qtdVertices];
    bool visitado[qtdVertices];
    bool articulacao[qtdVertices];
    int qtdArticulacao(0);
    int pais[qtdVertices];
    int indiceAtual = 0;
    for (int i = 0; i < qtdVertices; i++) {
        disc[i] = -1;
        low[i] = -1;
        visitado[i] = false;
        articulacao[i] = false;
        pais[i] = -1;
    }
    for (int i = 0; i < qtdVertices; i++) {
        if (disc[i] == -1) {
            DFSArticulacao(i, disc, low, visitado, pais, articulacao, indiceAtual, qtdArticulacao);
        }
    }
    if(qtdArticulacao == 0)
        std::cout << -1;
    for (int i = 0; i < qtdVertices; i++) {
        if (articulacao[i]) {
            std::cout << i << " ";
        }
    }
    std::cout << std::endl;
}

void Grafo::DFSArticulacao(int u, int disc[], int low[], bool visitado[], int pais[], bool articulacao[], int& indiceAtual, int& qtdArticulacao) {
    visitado[u] = true;
    disc[u] = low[u] = indiceAtual++;
    int filhos = 0;
    for (int i = 0; i < listaAdj[u].size(); i++) {
        Aresta a = listaAdj[u][i];
        int v = a.v_entrada;
        if (!visitado[v]) {
            pais[v] = u;
            filhos++;
            DFSArticulacao(v, disc, low, visitado, pais, articulacao, indiceAtual, qtdArticulacao);
            low[u] = std::min(low[u], low[v]);
            if (pais[u] == -1 && filhos > 1){
                articulacao[u] = true;
                qtdArticulacao++;
            }
            if (pais[u] != -1 && low[v] >= disc[u]) {
                articulacao[u] = true;
                qtdArticulacao++;
            }
        } else if (v != pais[u]) {
            low[u] = std::min(low[u], disc[v]);
        }
    }
}

void Grafo::ArestasPonte() {
    int disc[qtdVertices];
    int low[qtdVertices];
    bool visitado[qtdVertices];
    int pais[qtdVertices];
    int arestasPonte{0};
    int indiceAtual = 0;
    for (int i = 0; i < qtdVertices; i++) {
        disc[i] = -1;
        low[i] = -1;
        visitado[i] = false;
        pais[i] = -1;
    }
    for (int i = 0; i < qtdVertices; i++) {
        if (!visitado[i]) {
            DFSPonte(i, disc, low, visitado, pais, arestasPonte, indiceAtual);
        }   
    }
    std::cout << arestasPonte << std::endl;
}

void Grafo::DFSPonte(int u, int disc[], int low[], bool visitado[], int pais[], int& arestasPonte, int& indiceAtual) {
    visitado[u] = true;
    disc[u] = low[u] = indiceAtual++;
    for (int i{0}; i < listaAdj[u].size(); i++) {
        Aresta a = listaAdj[u][i];
        int v = a.v_entrada;
        if (!visitado[v]) {
            pais[v] = u;
            DFSPonte(v, disc, low, visitado, pais, arestasPonte, indiceAtual);
            low[u] = std::min(low[u], low[v]);
            if (low[v] > disc[u]) {
                arestasPonte++;
            }
        } else if (v != pais[u]) {
            low[u] = std::min(low[u], disc[v]);
        }
    }
}

void Grafo::OrdenaLista(){
    for(int i{0}; i < qtdVertices; i++){
        sort(listaAdj[i].begin(), listaAdj[i].end());
    }
}

int* Grafo::BFS(){
    enum cores {BRANCO, CINZA, PRETO};
    int* pais = new int[qtdVertices];
    for(int i{0}; i < qtdVertices; i++)
        pais[i] = i;
    cores coloracao[qtdVertices];
    for(int i = 1; i < qtdVertices; i++){
        coloracao[i] = BRANCO;
    }
    std::queue<int> fila;
    fila.push(0);
    coloracao[0] = CINZA;
    while(!fila.empty()){
        int atual = fila.front();
        fila.pop();
        for(int i = 0; i < listaAdj[atual].size(); i++){
            Aresta a = listaAdj[atual][i];
            if(coloracao[a.v_entrada] == BRANCO){
                coloracao[a.v_entrada] = CINZA;
                fila.push(a.v_entrada);
                pais[a.v_entrada] = atual;
            }
        }
        coloracao[atual] = PRETO;
    }
    return pais;
}

int* Grafo::DFS(){
    enum cores {BRANCO, CINZA, PRETO};
    int* pais = new int[qtdVertices];
    for(int i{0}; i < qtdVertices; i++)
        pais[i] = i;
    cores coloracao[qtdVertices];
    for(int i = 1; i < qtdVertices; i++){
        coloracao[i] = BRANCO;
    }
    std::stack<int> pilha;
    pilha.push(0);
    coloracao[0] = CINZA;
    int atual = pilha.top();
    bool achou = false;
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
            pais[a.v_entrada] = atual;
            i++;
        }
        if(achou == false){
            pilha.pop();
            coloracao[atual] = PRETO;
        }
    }
    return pais;
}

class GrafoResidual : public Grafo {
    public: 
        GrafoResidual(int n);
        void AdicionaAresta(int id, int u, int v, int peso);
        void Atualiza(int pais[], int fluxo);
        int MenorFluxo(int pais[]);
        int ResBFS(int pais[]);
};

GrafoResidual::GrafoResidual(int n) : Grafo(n){}

void GrafoResidual::AdicionaAresta(int id, int u, int v, int peso){
    Aresta aresta;
    aresta.id = id;
    aresta.v_entrada = v;
    aresta.peso = peso;
    listaAdj[u].push_back(aresta);
    aresta.v_entrada = u;
    aresta.peso = 0;
    listaAdj[v].push_back(aresta);
}

int GrafoResidual::ResBFS(int pais[]){
    enum cores {BRANCO, CINZA, PRETO};
    for(int i{0}; i < qtdVertices; i++)
        pais[i] = -1;
    cores coloracao[qtdVertices];
    for(int i = 1; i < qtdVertices; i++){
        coloracao[i] = BRANCO;
    }
    std::queue<int> fila;
    fila.push(0);
    coloracao[0] = CINZA;
    while(!fila.empty()){
        int atual = fila.front();
        fila.pop();
        for(int i = 0; i < listaAdj[atual].size(); i++){
            Aresta a = listaAdj[atual][i];
            int peso = a.peso;
            if(coloracao[a.v_entrada] == BRANCO && peso>0){
                coloracao[a.v_entrada] = CINZA;
                fila.push(a.v_entrada);
                pais[a.v_entrada] = atual;
                if(a.v_entrada == qtdVertices - 1)
                    return 1;
            }
        }
        coloracao[atual] = PRETO;
    }
    return 0;
}

int GrafoResidual::MenorFluxo(int pais[]){
    int menor{INF};
    int a = qtdVertices - 1;
    while(pais[a] != -1){
        for(int i{0}; i < listaAdj[pais[a]].size(); i++){
            if(listaAdj[pais[a]][i].v_entrada == a){
                int p = listaAdj[pais[a]][i].peso;
                menor = std::min(menor, p);
                break;
            }
        }
        a = pais[a];
    }
    return menor;
}

void GrafoResidual::Atualiza(int pais[], int fluxo){
    int a = qtdVertices - 1;
    while(pais[a] != -1){
        for(int i{0}; i < listaAdj[pais[a]].size(); i++){
            if(listaAdj[pais[a]][i].v_entrada == a){
                listaAdj[pais[a]][i].peso -= fluxo;
            }
        }
        for(int i{0}; i < listaAdj[a].size(); i++){
            if(listaAdj[a][i].v_entrada == pais[a]){
                listaAdj[a][i].peso += fluxo;
            }
        }
        a = pais[a];
    }
}

class GrafoNaoDir : public Grafo {
    public:
        GrafoNaoDir(int n);
        int VerificaEuleriano();
        void AGM();
        void Gera_AGM();
        void AdicionaAresta(int id, int u, int v, int peso);
        void CaminhoMinimo();
        int VerificaCiclo(); 
        int VerificaConexidade();
        int ComponentesConexas();
        int VerificaBipartido();
        void Gera_Bipartido();
};

GrafoNaoDir::GrafoNaoDir(int n) : Grafo(n){}

int GrafoNaoDir::VerificaCiclo(){
    enum cores {BRANCO, CINZA, PRETO};
    cores coloracao[qtdVertices];
    for(int i = 1; i < qtdVertices; i++){
        coloracao[i] = BRANCO;
    }
    std::stack<int> pilha;
    pilha.push(0);
    coloracao[0] = CINZA;
    int vertices_pretos{0};
    int atual = pilha.top();
    bool achou = false;
    int ultimo; 
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
                    ultimo = atual;
                }
                else if(coloracao[a.v_entrada] == CINZA and a.v_entrada != ultimo)
                    return 1;
                i++;
            }
            if(achou == false){
                pilha.pop();
                coloracao[atual] = PRETO;
                vertices_pretos++;
            }
        }
        bool achouBranco = false;
        int i{0};
        while(achouBranco == false and i < qtdVertices){
            if(coloracao[i] == BRANCO){
                achouBranco = true;
                coloracao[i] = CINZA;
                pilha.push(i);
            }
            i++;
        }
    }
    return 0;
} 


void GrafoNaoDir::AdicionaAresta(int id, int u, int v, int peso){
    Aresta aresta;
    aresta.id = id;
    aresta.v_entrada = v;
    aresta.peso = peso;
    listaAdj[u].push_back(aresta);
    aresta.v_entrada = u;
    listaAdj[v].push_back(aresta);
}

int GrafoNaoDir::VerificaBipartido(){
    enum cores {BRANCO, AZUL, VERMELHO};
    cores coloracao[qtdVertices];
    for(int i = 1; i < qtdVertices; i++){
        coloracao[i] = BRANCO;
    }
    int vertices_coloridos{0};
    std::queue<int> fila;
    fila.push(0);
    coloracao[0] = AZUL;
    vertices_coloridos++;
    while(vertices_coloridos < qtdVertices){
        while(!fila.empty()){
            int atual = fila.front();
            fila.pop();
            for(int i = 0; i < listaAdj[atual].size(); i++){
                Aresta a = listaAdj[atual][i];
                if(coloracao[a.v_entrada] == BRANCO){
                    if(coloracao[atual] == AZUL){
                        coloracao[a.v_entrada] = VERMELHO;
                        vertices_coloridos++;
                    }
                    else{
                        coloracao[a.v_entrada] = AZUL;
                        vertices_coloridos++;
                    }
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
                vertices_coloridos++;
            }
        i++;
        }
    }
    return 1;
}


void GrafoNaoDir::AGM(){
    std::vector<OrdAresta> arestas_ord;
    int nArestas{0};
    OrdAresta arestaO;
    for(int i{0}; i < qtdVertices; i++){
        for(int j{0}; j < listaAdj[i].size(); j++){
            arestaO.v_saida = i;
            arestaO.aresta.id = listaAdj[i][j].id;
            arestaO.aresta.peso = listaAdj[i][j].peso;
            arestaO.aresta.v_entrada = listaAdj[i][j].v_entrada;
            arestas_ord.push_back(arestaO);
            nArestas++;
        }
    }
    std::sort(arestas_ord.begin(), arestas_ord.end(), [](const OrdAresta& a, const OrdAresta& b) {
        return a.aresta.peso < b.aresta.peso;
    });
    int soma{0};
    DisjointSet conj(qtdVertices);  
    for(int i{0}; i < nArestas; i++){
        int v = arestas_ord[i].v_saida;
        int u = arestas_ord[i].aresta.v_entrada; 
        if(conj.encontraSet(v) != conj.encontraSet(u)){
            soma += arestas_ord[i].aresta.peso;
            conj.une(v, u);
        }
    }
    std::cout << soma << std::endl;
}

int GrafoNaoDir::ComponentesConexas(){
    enum cores {BRANCO, CINZA, PRETO};
    cores coloracao[qtdVertices];
    for(int i = 1; i < qtdVertices; i++){
        coloracao[i] = BRANCO;
    }
    std::queue<int> fila;
    fila.push(0);
    coloracao[0] = CINZA;
    int num_componentes{1};
    int v_pretos{0};
    while(v_pretos < qtdVertices){
        while(!fila.empty()){
            int atual = fila.front();
            fila.pop();
            for(int i = 0; i < listaAdj[atual].size(); i++){
                Aresta a = listaAdj[atual][i];
                if(coloracao[a.v_entrada] == BRANCO){
                    coloracao[a.v_entrada] = CINZA;
                    fila.push(a.v_entrada);
                }
            }
            coloracao[atual] = PRETO;
            v_pretos++;
        }
        bool achou = false;
        int i{0};
        while(achou == false and i < qtdVertices){
            if(coloracao[i] == BRANCO){
                num_componentes++;
                achou = true;
                coloracao[i] = CINZA;
                fila.push(i);
            }
            i++;
        }
    }
    return num_componentes;
}

int GrafoNaoDir::VerificaConexidade(){
    int* pais = new int[qtdVertices];
    pais = BFS();
    for(int i{1}; i < qtdVertices; i++){
        if(pais[i]==i)
            return 0;
    }
    delete[] pais;
    return 1;
}

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

void GrafoNaoDir::CaminhoMinimo(){
    int distancias[qtdVertices];
    bool ativv[qtdVertices];
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int,int>>, std::greater<std::pair<int, int>>> minHeap;       
    for(int i{i}; i < qtdVertices; i++){
        minHeap.push({INF, i});
        distancias[i] = INF;
        ativv[i] = true;
    }
    distancias[0] = 0;
    ativv[0] = true;
    minHeap.push({0, 0});
    while(!minHeap.empty()){
        std::pair par = minHeap.top();
        int u = par.second;
        minHeap.pop();
        if(ativv[u])
            for(int i{0}; i < listaAdj[u].size(); i++){
                Aresta a = listaAdj[u][i];
                if(distancias[a.v_entrada] > (distancias[u] + a.peso)){
                    distancias[a.v_entrada] = distancias[u] + a.peso;
                    minHeap.push({distancias[a.v_entrada], a.v_entrada});
                }
            }
        }
    std::cout << distancias[qtdVertices-1];
}


class GrafoDir : public Grafo {
    public:
        GrafoDir(int n);
        void AdicionaAresta(int id, int u, int v, int peso);
        int VerificaEuleriano();
        int ComponentesFortementeConexas();
        void ComponentesFortementeConexasAux(int vertice, int indice[], int low[], bool naPilha[], std::stack<int>& pilha, int& indiceAtual, int& componentesConexas);
        void OrdemTopologica();
        void FluxoMaximo();
        int VerificaCiclo(); 
        void FechoTransitivo();
        int VerificaConexidade();
};

GrafoDir::GrafoDir(int n) : Grafo(n){}

int GrafoDir::VerificaCiclo(){
    enum cores {BRANCO, CINZA, PRETO};
    cores coloracao[qtdVertices];
    for(int i = 1; i < qtdVertices; i++){
        coloracao[i] = BRANCO;
    }
    std::stack<int> pilha;
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
                else if(coloracao[a.v_entrada] == CINZA)
                    return 1;
                i++;
            }
            if(achou == false){
                pilha.pop();
                coloracao[atual] = PRETO;
                vertices_pretos++;
            }
        }
        bool achouBranco = false;
        int i{0};
        while(achouBranco == false and i < qtdVertices){
            if(coloracao[i] == BRANCO){
                achouBranco = true;
                coloracao[i] = CINZA;
                pilha.push(i);
            }
            i++;
        }
    }
    return 0;
} 


int GrafoDir::ComponentesFortementeConexas(){
    int indice[qtdVertices];
    int low[qtdVertices];
    bool naPilha[qtdVertices];
    for(int i{0}; i < qtdVertices; i++){
        indice[i] = -1;
        low[i] = -1;
        naPilha[i] = false;
    }
    std::stack<int> pilha;
    int indiceAtual{0};
    int componentesConexas{0};
    for(int i{0}; i < qtdVertices; i++){
        if(indice[i] == -1)
            ComponentesFortementeConexasAux(i, indice, low, naPilha, pilha, indiceAtual, componentesConexas);
    }
    return componentesConexas;
}

void GrafoDir::ComponentesFortementeConexasAux(int vertice, int indice[], int low[], bool naPilha[], std::stack<int>& pilha, int& indiceAtual, int& componentesConexas) {
    pilha.push(vertice);
    indice[vertice] = indiceAtual;
    low[vertice] = indiceAtual;
    naPilha[vertice] = true;
    indiceAtual++;
    for (int i{0}; i < listaAdj[vertice].size(); i++) {
        Aresta a = listaAdj[vertice][i];
        if (indice[a.v_entrada] == -1){
            ComponentesFortementeConexasAux(a.v_entrada, indice, low, naPilha, pilha, indiceAtual, componentesConexas);
            low[vertice] = std::min(low[vertice], low[a.v_entrada]); 
        }
        else if (naPilha[a.v_entrada])
            low[vertice] = std::min(low[vertice], indice[a.v_entrada]);
    }
    if (low[vertice] == indice[vertice]) {
        int aux;
        do {
            aux = pilha.top();
            pilha.pop();
            naPilha[aux] = false;
        } while (aux != vertice);
        componentesConexas++;
    }
}

void GrafoDir::AdicionaAresta(int id, int u, int v, int peso){
    Aresta aresta;
    aresta.id = id;
    aresta.v_entrada = v;
    aresta.peso = peso;
    listaAdj[u].push_back(aresta);
}

int GrafoDir::VerificaConexidade(){
    GrafoNaoDir grafo_aux(qtdVertices);
    for(int i{0}; i < qtdVertices; i++){
        for(int j{0}; j < listaAdj[i].size(); j++){
            int id = listaAdj[i][j].id;
            int v = listaAdj[i][j].v_entrada;
            int u = i;
            grafo_aux.AdicionaAresta(id, v, u, 1);
        }
    }
    return grafo_aux.VerificaConexidade();
}

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
                pilha.push(i);
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


int GrafoDir::VerificaEuleriano(){
    int CFC = ComponentesFortementeConexas();
    if(CFC != 1)
        return 0;
    int matriz_vertices[qtdVertices][2];
    for(int i{0}; i < qtdVertices; i++){
        matriz_vertices[i][0] = listaAdj[i].size();
        matriz_vertices[i][1] = 0;
    }
    for(int i{0}; i < qtdVertices; i++){
        for(int j{0}; j < listaAdj[i].size(); j++){
            matriz_vertices[listaAdj[i][j].v_entrada][1]++;
        }
    }
    for(int i{0}; i < qtdVertices; i++){
        if(matriz_vertices[i][0] != matriz_vertices[i][1])
            return 0;
    }
    return 1;
}


void GrafoDir::FluxoMaximo(){
    GrafoResidual grafoResidual(qtdVertices);
    for(int i{0}; i < qtdVertices; i++){
        for(int j{0}; j < listaAdj[i].size(); j++){
            Aresta a = listaAdj[i][j];
            int u = a.v_entrada;
            int p = a.peso;
            grafoResidual.AdicionaAresta(0, i, u, p);
        }
    }
    int fluxoMaximo{0};
    int continua;
    int pais[qtdVertices];
    do{
        continua = grafoResidual.ResBFS(pais);
        if(continua){
            int fluxo = grafoResidual.MenorFluxo(pais);
            fluxoMaximo += fluxo;
            grafoResidual.Atualiza(pais, fluxo);
        }

    }while(continua);
    std::cout << fluxoMaximo;
}

void GrafoDir::FechoTransitivo(){
    enum cores {BRANCO, CINZA, PRETO};
    cores coloracao[qtdVertices];
    for(int i = 1; i < qtdVertices; i++){
        coloracao[i] = BRANCO;
    }
    std::vector<int> fecho;
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
                fecho.push_back(a.v_entrada);
            }
            i++;
        }
        if(achou == false){
            pilha.pop();
            coloracao[atual] = PRETO;
        }
    }
    std::sort(fecho.begin(), fecho.end());
    for(int i{0}; i < fecho.size(); i++){
        std::cout << fecho[i] << " ";
    }
    std::cout << std::endl;
} 

void Grafo::Gera_BFS(char simbolo){
    enum cores {BRANCO, CINZA, PRETO};
    cores coloracao[qtdVertices];
    std::system("> BFS.dot");
    if(simbolo == '>'){
        std::system("echo -e 'digraph{\n' > BFS.dot");
    }
    else if(simbolo == '-'){
        std::system("echo -e 'graph{\n' > BFS.dot");
    }
    std::string aux = "echo -e '";
    for(int i{0}; i < qtdVertices; i++){
        aux = aux + std::to_string(i);
        aux.push_back('\n');
    }
    aux = aux + "'";
    aux = aux + " >> BFS.dot";
    const char* vertices = aux.c_str();
    std::system(vertices);
    for(int i = 1; i < qtdVertices; i++){
        coloracao[i] = BRANCO;
    }
    std::queue<int> fila;
    fila.push(0);
    coloracao[0] = CINZA;
    int v_pretos{0};
    while(v_pretos < qtdVertices){
        while(!fila.empty()){
            int atual = fila.front();
            fila.pop();
            for(int i = 0; i < listaAdj[atual].size(); i++){
                Aresta a = listaAdj[atual][i];
                if(coloracao[a.v_entrada] == BRANCO){
                    std::string comando_s = "echo -e '";
                    comando_s = comando_s + std::to_string(atual);
                    comando_s = comando_s + " -";
                    comando_s.push_back(simbolo);
                    comando_s = comando_s + " " + std::to_string(a.v_entrada);
                    comando_s = comando_s + "\n' >> BFS.dot"; 
                    const char* comando = comando_s.c_str();
                    std::system(comando);
                    coloracao[a.v_entrada] = CINZA;
                    fila.push(a.v_entrada);
                }
            }
            coloracao[atual] = PRETO;
            v_pretos++;
        }
        bool achou = false;
        int i{0};
        while(achou == false and i < qtdVertices){
            if(coloracao[i] == BRANCO){
                achou = true;
                coloracao[i] = CINZA;
                fila.push(i);
            }
            i++;
        }
    }
    std::system("echo '}' >> BFS.dot");
    std::system("dot -Tpng BFS.dot > BFS.png");
}

void Grafo::Gera_DFS(char simbolo){
    enum cores {BRANCO, CINZA, PRETO};
    cores coloracao[qtdVertices];
    std::system("> DFS.dot");
    if(simbolo == '>'){
        std::system("echo -e 'digraph{\n' > DFS.dot");
    }
    else if(simbolo == '-'){
        std::system("echo -e 'graph{\n' > DFS.dot");
    }
    for(int i = 1; i < qtdVertices; i++){
        coloracao[i] = BRANCO;
    }
    std::string aux = "echo -e '";
    for(int i{0}; i < qtdVertices; i++){
        aux = aux + std::to_string(i);
        aux.push_back('\n');
    }
    aux = aux + "'";
    aux = aux + " >> DFS.dot";
    const char* vertices = aux.c_str();
    std::system(vertices);
    std::stack<int> pilha;
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
                    std::string comando_s = "echo -e '";
                    comando_s = comando_s + std::to_string(atual);
                    comando_s = comando_s + " -";
                    comando_s.push_back(simbolo);
                    comando_s = comando_s + " " + std::to_string(a.v_entrada);
                    comando_s = comando_s + "\n' >> DFS.dot"; 
                    const char* comando = comando_s.c_str();
                    std::system(comando);
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
            }
        }
        bool achouBranco = false;
        int i{0};
        while(achouBranco == false and i < qtdVertices){
            if(coloracao[i] == BRANCO){
                achouBranco = true;
                coloracao[i] = CINZA;
                pilha.push(i);
            }
            i++;
        }
    }
    std::system("echo '}' >> DFS.dot");
    std::system("dot -Tpng DFS.dot > DFS.png");
}

void GrafoNaoDir::Gera_Bipartido(){
    enum cores {BRANCO, AZUL, VERMELHO};
    cores coloracao[qtdVertices];
    for(int i = 1; i < qtdVertices; i++){
        coloracao[i] = BRANCO;
    }
    std::system("> Bipartido.dot");
    std::system("echo -e 'strict graph{\nsubgraph Cluster_1{\nstyle=dashed\n' >> Bipartido.dot");
    int vertices_coloridos{0};
    std::queue<int> fila;
    fila.push(0);
    std::queue<int> particao_1;
    std::queue<int> particao_2;
    std::queue<std::pair<int, int>> arestas;
    coloracao[0] = AZUL;
    particao_1.push(0);
    vertices_coloridos++;
    while(vertices_coloridos < qtdVertices){
        while(!fila.empty()){
            int atual = fila.front();
            fila.pop();
            for(int i = 0; i < listaAdj[atual].size(); i++){
                Aresta a = listaAdj[atual][i];
                arestas.push(std::make_pair(atual, a.v_entrada));
                if(coloracao[a.v_entrada] == BRANCO){
                    if(coloracao[atual] == AZUL){
                        coloracao[a.v_entrada] = VERMELHO;
                        vertices_coloridos++;
                        particao_2.push(a.v_entrada);
                    }
                    else{
                        coloracao[a.v_entrada] = AZUL;
                        vertices_coloridos++;
                        particao_1.push(a.v_entrada);
                    }
                    fila.push(a.v_entrada);
                }
            }
        }
        int i = 0;
        bool achou = false;
        while(i < qtdVertices && achou == false){
            if(coloracao[i] == BRANCO){
                coloracao[i] = AZUL;
                particao_1.push(i);
                fila.push(i);
                achou = true;
                vertices_coloridos++;
            }
        i++;
        }
    }
    std::string comando_s = "echo -e '";
    while(!particao_1.empty()){
        int p1 = particao_1.front();
        particao_1.pop();
        comando_s = comando_s + std::to_string(p1) + " [color=red]\n";
    }
    comando_s = comando_s + "}\n' >> Bipartido.dot";
    const char* comando = comando_s.c_str();
    std::system(comando);
    std::system("echo -e 'subgraph Cluster_2{\nstyle=dashed\n' >> Bipartido.dot");
    comando_s = "echo -e '";
    while(!particao_2.empty()){
        int p2 = particao_2.front();
        particao_2.pop();
        comando_s = comando_s + std::to_string(p2) + " [color=blue]\n";
    }
    comando_s = comando_s + "}\n' >> Bipartido.dot";
    comando = comando_s.c_str();
    std::system(comando);
    comando_s = "echo -e '";
    while(!arestas.empty()){
        std::pair<int, int> par = arestas.front();
        arestas.pop();
        int p1 = par.first;
        int p2 = par.second;
        comando_s = comando_s + std::to_string(p1) + " -- " + std::to_string(p2) + "\n";
    }
    comando_s = comando_s + "}' >> Bipartido.dot";
    comando = comando_s.c_str();
    std::system(comando);
    std::system("dot -Tpng Bipartido.dot > Bipartido.png");
}

void GrafoNaoDir::Gera_AGM(){
    std::vector<OrdAresta> arestas_ord;
    int nArestas{0};
    OrdAresta arestaO;
    std::system("> AGM.dot");
    std::system("echo -e 'graph{\n' >> AGM.dot");
    for(int i{0}; i < qtdVertices; i++){
        for(int j{0}; j < listaAdj[i].size(); j++){
            arestaO.v_saida = i;
            arestaO.aresta.id = listaAdj[i][j].id;
            arestaO.aresta.peso = listaAdj[i][j].peso;
            arestaO.aresta.v_entrada = listaAdj[i][j].v_entrada;
            arestas_ord.push_back(arestaO);
            nArestas++;
        }
    }
    std::sort(arestas_ord.begin(), arestas_ord.end(), [](const OrdAresta& a, const OrdAresta& b) {
        return a.aresta.peso < b.aresta.peso;
    });
    int soma{0};
    DisjointSet conj(qtdVertices);  
    std::string comando_s;
    for(int i{0}; i < nArestas; i++){
        int v = arestas_ord[i].v_saida;
        int u = arestas_ord[i].aresta.v_entrada; 
        if(conj.encontraSet(v) != conj.encontraSet(u)){
            comando_s = "echo -e '";
            comando_s += std::to_string(v);
            comando_s += "--";
            comando_s += std::to_string(u);
            comando_s += " [label=\"";
            comando_s += std::to_string(arestas_ord[i].aresta.peso);
            comando_s += "\" weight=";
            comando_s += std::to_string(arestas_ord[i].aresta.peso);
            comando_s.push_back(']');
            comando_s += "\n' >> AGM.dot";
            const char* comando = comando_s.c_str();
            std::system(comando);
            soma += arestas_ord[i].aresta.peso;
            conj.une(v, u);
        }
    }
    comando_s = "echo -e '\"SOMA TOTAL = ";
    comando_s += std::to_string(soma);
    comando_s += "\"\n}' >> AGM.dot";
    const char* comando = comando_s.c_str();
    std::system(comando);
    std::system("dot -Tpng AGM.dot > AGM.png");
}

int main(){
    int temp;
    std::vector<int> funcoes;
    while (std::cin >> temp) {
        funcoes.push_back(temp);
    }
    std::cin.clear();
    int nArestas = funcoes.back();
    funcoes.pop_back();
    int nVertices = funcoes.back();
    funcoes.pop_back();
    std::string tipo;
    std::cin >> tipo;
    int idAresta, vertice_v, vertice_u, peso;
        GrafoNaoDir grafoNaoDir(nVertices);
    if(tipo == "nao_direcionado"){
        for(int i = 0; i < nArestas; i++){
            std::cin >> idAresta >> vertice_v >> vertice_u >> peso;
            grafoNaoDir.AdicionaAresta(idAresta, vertice_v, vertice_u, peso);
        }
        grafoNaoDir.OrdenaLista();
        for (int valor : funcoes){ 
            int aux;
            switch (valor) {
                case 0:
                    aux = grafoNaoDir.VerificaConexidade();
                    std::cout << aux << std::endl;
                    break;
                case 1:
                    aux = grafoNaoDir.VerificaBipartido();
                    std::cout << aux << std::endl;
                    if(aux)
                        grafoNaoDir.Gera_Bipartido();
                    break;
                case 2:
                    aux = grafoNaoDir.VerificaEuleriano();
                    std::cout << aux << std::endl;
                    break;
                case 3:
                    aux = grafoNaoDir.VerificaCiclo();
                    std::cout << aux << std::endl;
                    break;
                case 4:
                    aux = grafoNaoDir.ComponentesConexas();
                    std::cout << aux << std::endl;
                    break;
                case 5:
                    std::cout << -1 << std::endl;
                    break;
                case 6:
                    grafoNaoDir.VerticesArticulacao();
                    break;
                case 7:
                    grafoNaoDir.ArestasPonte();
                    break;
                case 8:
                    grafoNaoDir.Exibe_DFS();
                    std::cout << std::endl;
                    grafoNaoDir.Gera_DFS('-');
                    break;
                case 9:
                    grafoNaoDir.Exibe_BFS();
                    grafoNaoDir.Gera_BFS('-');
                    std::cout << std::endl;
                    break;
                case 10:
                    grafoNaoDir.AGM();
                    grafoNaoDir.Gera_AGM();
                    break;
                case 11:
                    std::cout << -1 << std::endl;
                    break;
                case 12:
                    grafoNaoDir.CaminhoMinimo();
                    std::cout << std::endl;
                    break;
                case 13:
                    std::cout << -1 << std::endl;
                    break;
                case 14:
                    std::cout << -1 << std::endl;
                    break;
            }
        }
    }
    else if(tipo == "direcionado"){
        GrafoDir grafoDir(nVertices);
        for(int i = 0; i < nArestas; i++){
            std::cin >> idAresta >> vertice_v >> vertice_u >> peso;
            grafoDir.AdicionaAresta(idAresta, vertice_v, vertice_u, peso);
        }
        grafoDir.OrdenaLista();
        for (int valor : funcoes){ 
            int aux;
            switch (valor) {
                case 0:
                    aux = grafoDir.VerificaConexidade();
                    std::cout << aux << std::endl;
                    break;
                case 1:
                    std::cout << -1 << std::endl;
                    break;
                case 2:
                    aux = grafoDir.VerificaEuleriano();
                    std::cout << aux << std::endl;
                    break;
                case 3:
                    aux = grafoDir.VerificaCiclo();
                    std::cout << aux << std::endl;
                    break;
                case 4:
                    std::cout << -1 << std::endl;
                    break;
                case 5:
                    grafoDir.ComponentesFortementeConexas();
                    break;
                case 6:
                    std::cout << -1 << std::endl;
                    break;
                case 7:
                    std::cout << -1 << std::endl;
                    break;
                case 8:
                    grafoDir.Exibe_DFS();
                    std::cout << std::endl;
                    grafoDir.Gera_DFS('>');
                    break;
                case 9:
                    grafoDir.Exibe_BFS();
                    std::cout << std::endl;
                    grafoDir.Gera_BFS('>');
                    break;
                case 10:
                    std::cout << -1 << std::endl;
                    break;
                case 11:
                    grafoDir.OrdemTopologica();
                    break;
                case 12:
                    std::cout << -1 << std::endl;
                    break;
                case 13:
                    grafoDir.FluxoMaximo();
                    std::cout << std::endl;
                    break;
                case 14:
                    grafoDir.FechoTransitivo();
                    break;
            }
        }      
     }
}