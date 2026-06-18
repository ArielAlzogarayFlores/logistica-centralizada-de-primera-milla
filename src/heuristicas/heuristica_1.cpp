#include <limits.h>
#include "heuristica_1.h"
#include <vector>

Solution heuristica_1(const GAPInstance& instance, int cmax) {
    // creamos una solución vacía
    Solution solucion;
    solucion.vendedores_sin_asignar = 0;
    solucion.costo_total = 0;
    // creamos asignaciones para guardar las decisiones que vayamos tomando según la heurística (constructiva)
    std::vector<std::vector<int>> asignaciones(instance.m);
    // creamos una copia de las capacidades de la instancia de GAP provista
    std::vector<int> capacidades_residuales = instance.capacidades;
    for (int j = 0; j<instance.n; j++) { // por cada vendedor j buscamos el depósito asignable i más cercano
        int deposito_minimo = -1; // empezamos sin depósito mínimo
        int costo_minimo = INT_MAX; // consecuencia de lo anterior: el costo (distancia) es infinito
        for (int i=0; i<instance.m; i++) {
            // verificamos que sea el depósito más cercano y que sea asignable
            if (instance.costos[i][j] < costo_minimo && capacidades_residuales[i] - instance.demandas[i][j] >= 0) {
                deposito_minimo = i;
                costo_minimo = instance.costos[i][j];
            }
        }
        // si tras evaluar sobre todos los depósitos el vendedor j se halla un depósito asignable i más cercano se toma la decisión de asignarlo a dicho depósito
        if (deposito_minimo != -1) {
            asignaciones[deposito_minimo].push_back(j);
            capacidades_residuales[deposito_minimo] = capacidades_residuales[deposito_minimo] - instance.demandas[deposito_minimo][j];
            solucion.costo_total += instance.demandas[deposito_minimo][j];
        } else { // en caso contrario se lo cuenta al vendedor j como un vendedor sin asignar
            solucion.vendedores_sin_asignar++;
        }
    }
    solucion.asignaciones = asignaciones;
    // aplicamos la penalización (si es que la hay)
    solucion.costo_total += (3*cmax)*solucion.vendedores_sin_asignar;
    return solucion;
}