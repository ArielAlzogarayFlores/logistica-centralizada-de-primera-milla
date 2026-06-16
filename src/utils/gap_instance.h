#ifndef GAP_INSTANCE_H
#define GAP_INSTANCE_H

#include <vector>
#include <string>

struct GAPInstance {

    int m; // agentes / depositos
    int n; // trabajos / vendedores

    // costos[i][j]
    std::vector<std::vector<int>> costos;

    // recursos[i][j]
    std::vector<std::vector<int>> recursos;

    // capacidad[i]
    std::vector<int> capacidades;
};

GAPInstance read_instance(const std::string& filename);

int c_max(
    const std::vector<int>& N,
    const std::vector<int>& M,
    const std::vector<std::vector<int>>& costos
);

#endif