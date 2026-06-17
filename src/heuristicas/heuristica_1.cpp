#include <limits.h>
#include "heuristica_1.h"
#include <vector>

Solution heuristica_1(const GAPInstance& instance, int cmax) {
    Solution solucion;
    solucion.vendedores_sin_asignar = 0;
    solucion.costo_total = 0;
    std::vector<std::vector<int>> asignaciones(instance.m);
    std::vector<int> capacidades_residuales = instance.capacidades;
    for (int j = 0; j<instance.n; j++) {
        int deposito_minimo = -1; // Empezamos sin depósito mínimo
        int costo_minimo = INT_MAX; // Consecuencia de lo anterior
        for (int i=0; i<instance.m; i++) {
            if (instance.costos[i][j] < costo_minimo && capacidades_residuales[i] - instance.demandas[i][j] >= 0) {
                deposito_minimo = i;
                costo_minimo = instance.costos[i][j];
            }
        }
        if (deposito_minimo != -1) {
            asignaciones[deposito_minimo].push_back(j);
            capacidades_residuales[deposito_minimo] = capacidades_residuales[deposito_minimo] - instance.demandas[deposito_minimo][j];
            solucion.costo_total += instance.demandas[deposito_minimo][j];
        } else {
            solucion.vendedores_sin_asignar++;
        }
    }
    solucion.asignaciones = asignaciones;
    solucion.costo_total += (3*cmax)*solucion.vendedores_sin_asignar;
    return solucion;
}