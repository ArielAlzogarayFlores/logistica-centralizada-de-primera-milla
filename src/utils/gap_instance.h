#ifndef GAP_INSTANCE_H
#define GAP_INSTANCE_H

#include <vector>
#include <string>

struct GAPInstance {

    int m; // depositos
    int n; // vendedores

    // costos[i][j]
    std::vector<std::vector<int>> costos;

    // demandas[i][j]
    std::vector<std::vector<int>> demandas;

    // capacidad[i]
    std::vector<int> capacidades;
};

GAPInstance read_instance(const std::string& filename);

int costo_max(
    const std::vector<int>& N,
    const std::vector<int>& M,
    const std::vector<std::vector<int>>& costos
);

#endif