#ifndef SRC_SOLUTION_H
#define SRC_SOLUTION_H

#include <vector>

struct Solution {
    // los depósitos con los vendedores asignados
    std::vector<std::vector<int>> asignaciones;

    int costo_total;

    // cantidad de vendedores sin asignar
    int vendedores_sin_asignar;

    // para determinar si la solución es parcial o no
    bool parcial() const {
        return vendedores_sin_asignar > 0;
    }
};

#endif
