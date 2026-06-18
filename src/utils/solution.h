#ifndef SRC_SOLUTION_H
#define SRC_SOLUTION_H

#include <vector>

struct Solution {
    // los depósitos con los vendedores asignados
    std::vector<std::vector<int>> asignaciones;

    int costo_total;

    // cantidad de vendedores sin asignar
    int vendedores_sin_asignar;

    // los vendedores asignados a depósitos -> para ahorrar calculos
    std::vector<int> asignaciones_vendedores;

    // capacidades residuales de cada depósito
    std::vector<int> capacidades_residuales;

    // para determinar si la solución es parcial o no
    bool parcial() const {
        return vendedores_sin_asignar > 0;
    }
};

#endif
