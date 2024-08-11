#include <iostream>
#include <stack>
#include <algorithm>
#include <queue>
#include <vector>
#include <string>
#include "GrafoDir.hpp"
#include "GrafoNaoDir.hpp"
#include "GrafoDir.hpp"
#include "DisjointSet.hpp"


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