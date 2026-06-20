#include <limits>
#include "heuristica_3.h"
#include <vector>

Solution heuristica_3 (const GAPInstance& instance, double cmax) {
    // creamos una solución vacía
    Solution solucion;
    solucion.vendedores_sin_asignar = 0;
    solucion.costo_total = 0.0;

    // creamos asignaciones para guardar las decisiones que vayamos tomando según la heurística (constructiva)
    std::vector<std::vector<int>> asignaciones(instance.m);

    // en paralelo hacemos algo similar pero para los vendedores con sus depósitos asignados
    std::vector<int> asignaciones_vendedores(instance.n);

    // creamos una copia de las capacidades de la instancia de GAP provista
    std::vector<double> capacidades_residuales = instance.capacidades;

    // creamos un vector vendedores_disponibles para saber qué vendedores aún no han sido asignados
    std::vector<bool> vendedores_disponibles(instance.n, true);

    // por cada depósito i buscamos los j's vendedores disponibles y asignables más cercanos hasta llenar el depósito
    for (int i=0; i<instance.m; i++) {
        // mientras halla capacidad
        bool asignacion_posible = true;
        while (asignacion_posible) {
            // empezamos sin vendedor mínimo
            int vendedor_minimo = -1;

            // consecuencia de lo anterior: el costo (distancia) es infinito
            double costo_minimo = std::numeric_limits<double>::infinity();

            for (int j=0; j<vendedores_disponibles.size(); j++) {
                // verificamos que sea el vendedor disponible más cercano y que sea asignable (o sea, factible)
                if (vendedores_disponibles[j] && instance.costos[i][j] < costo_minimo && capacidades_residuales[i] - instance.demandas[i][j] >= 0.0) {
                    // si verifica la condición se actualiza el vendedor mínimo de i y el costo asociado
                    vendedor_minimo = j;
                    costo_minimo = instance.costos[i][j];
                }
            }

            // si tras evaluar sobre todos los vendedores disponibles, el depósito i halla un vendedor asignable j más cercano,
            // se toma la decisión de asignarlo a dicho vendedor
            if (vendedor_minimo != -1) {
                // concretamos la asignación
                asignaciones[i].push_back(vendedor_minimo);
                asignaciones_vendedores[vendedor_minimo] = i;

                // actualizamos las capacidades residuales, el costo acumulado y ponemos al vendedor j como no disponible
                capacidades_residuales[i] = capacidades_residuales[i] - instance.demandas[i][vendedor_minimo];
                solucion.costo_total += instance.costos[i][vendedor_minimo];
                vendedores_disponibles[vendedor_minimo] = false;
            }
            else { // en caso contrario no se habría hallado un vendedor mínimo por lo que el depósito se llenó o no hay vendedores disponibles
                asignacion_posible = false;
            }
        }
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