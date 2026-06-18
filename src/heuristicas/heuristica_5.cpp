#include <limits.h>
#include "heuristica_5.h"
#include <vector>

Solution heuristica_5(const GAPInstance &instance, int cmax){
    // creamos una solución vacía
    Solution solucion;
    solucion.vendedores_sin_asignar = 0;
    solucion.costo_total = 0;

    // creamos asignaciones para guardar las decisiones que vayamos tomando según la heurística (constructiva)
    std::vector<std::vector<int>> asignaciones(instance.m);

    // en paralelo hacemos algo similar pero para los vendedores con sus depósitos asignados
    std::vector<int> asignaciones_vendedores(instance.n);

    // creamos una copia de las capacidades de la instancia de GAP provista
    std::vector<int> capacidades_residuales = instance.capacidades;

    // creamos un vector vendedores_disponibles para saber qué vendedores aún no han sido asignados
    std::vector<bool> vendedores_disponibles(instance.n, true);

    int cota_superior = instance.n * instance.m;
    int contador = 0;

    while (contador <= cota_superior){
        for (int i = 0; i < instance.m; i++){
            int vendedor_minimo = -1;
            int costo_minimo = INT_MAX;
            for (int j = 0; j < instance.n; j++){
                if (vendedores_disponibles[j]  && costo_minimo > instance.costos[i][j] && capacidades_residuales[i] >= instance.demandas[i][j]){
                    vendedor_minimo = j;
                    costo_minimo = instance.costos[i][j];
                }
            }
            if (vendedor_minimo != -1){
                // concretamos la asignación
                asignaciones[i].push_back(vendedor_minimo);
                asignaciones_vendedores[vendedor_minimo] = i;

                // actualizamos las capacidades residuales, el costo acumulado y ponemos al vendedor j como no disponible
                capacidades_residuales[i] = capacidades_residuales[i] - instance.demandas[i][vendedor_minimo];
                solucion.costo_total += instance.costos[i][vendedor_minimo];
                vendedores_disponibles[vendedor_minimo] = false;
            }
        }
        contador += 1;
    }

    // Actualizamos los vendedores sin asignar
    for (int j=0; j<vendedores_disponibles.size(); j++) {
        if (vendedores_disponibles[j]) {
            solucion.vendedores_sin_asignar++;
            asignaciones_vendedores[j] = -1;
        }
    }

    // completamos la solución
    solucion.asignaciones = asignaciones;
    solucion.asignaciones_vendedores = asignaciones_vendedores;
    solucion.capacidades_residuales = capacidades_residuales;

    // aplicamos la penalización (si es que la hay)
    solucion.costo_total += (3*cmax)*solucion.vendedores_sin_asignar;
    return solucion;
}