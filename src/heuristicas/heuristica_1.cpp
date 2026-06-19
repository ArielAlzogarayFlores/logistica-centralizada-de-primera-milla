#include <limits>
#include "heuristica_1.h"
#include <vector>

Solution heuristica_1(const GAPInstance& instance, double cmax) {
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

    // por cada vendedor j buscamos el depósito asignable i más cercano
    for (int j = 0; j<instance.n; j++) {
        // empezamos sin depósito mínimo (los vendedores con depósito -1 son aquellos sin asignar)
        int deposito_minimo = -1;

        // consecuencia de lo anterior: el costo (distancia) es infinito
        double costo_minimo = std::numeric_limits<double>::infinity();

        for (int i=0; i<instance.m; i++) {
            // verificamos que sea el depósito más cercano y que sea asignable (o sea, factible)
            if (instance.costos[i][j] < costo_minimo && capacidades_residuales[i] - instance.demandas[i][j] >= 0.0) {
                // si verifica la condición se actualiza el depósito mínimo de j y el costo asociado
                deposito_minimo = i;
                costo_minimo = instance.costos[i][j];
            }
        }

        // si tras evaluar sobre todos los depósitos, el vendedor j halla un depósito asignable i más cercano,
        // se toma la decisión de asignarlo a dicho depósito
        if (deposito_minimo != -1) {
            // concretamos la asignación
            asignaciones[deposito_minimo].push_back(j);
            asignaciones_vendedores[j] = deposito_minimo;

            // actualizamos las capacidades residuales y el costo acumulado
            capacidades_residuales[deposito_minimo] = capacidades_residuales[deposito_minimo] - instance.demandas[deposito_minimo][j];
            solucion.costo_total += instance.costos[deposito_minimo][j];

        } else { // en caso contrario se lo cuenta al vendedor j como un vendedor sin asignar
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