#pragma once

#include <vector>
#include <string>

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