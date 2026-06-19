#ifndef GAP_INSTANCE_H
#define GAP_INSTANCE_H

#include <vector>
#include <string>

struct GAPInstance {

    int m; // depósitos
    int n; // vendedores

    // costos[i][j]
    std::vector<std::vector<double>> costos;

    // demandas[i][j]
    std::vector<std::vector<double>> demandas;

    // capacidad[i]
    std::vector<double> capacidades;
};

GAPInstance read_instance(const std::string& filename);

double costo_max(
    const std::vector<int>& N,
    const std::vector<int>& M,
    const std::vector<std::vector<double>>& costos
);

#endif