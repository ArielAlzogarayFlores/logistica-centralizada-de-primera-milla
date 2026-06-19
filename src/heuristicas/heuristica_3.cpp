#include <limits>
#include "heuristica_3.h"
#include <algorithm>
#include <vector>

Solution heuristica_3(const GAPInstance &instance, double cmax) {
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

    // creamos un vector promedio_costo_vendedores para almacenar el costo promedio de cada vendedor
    std::vector<double> promedio_costo_vendedores = calcular_promedios(instance, capacidades_residuales, vendedores_disponibles);

    // por cada vendedor j
    for (int j=0; j<instance.n; j++) {
        // buscamos al vendedor cuyo promedio sea mínimo
        auto it = std::min_element(promedio_costo_vendedores.begin(), promedio_costo_vendedores.end());
        int vendedor_promedio_minimo = it - promedio_costo_vendedores.begin();

        // empezamos sin depósito mínimo (los vendedores con depósito -1 son aquellos sin asignar)
        int deposito_minimo = -1;

        // consecuencia de lo anterior: el costo (distancia) es infinito
        double costo_minimo = std::numeric_limits<double>::infinity();

        // buscamos el depósito más cercano al que podamos asignar al vendedor de promedio de costo mínimo
        for (int i=0; i<instance.m; i++) {
            // verificamos que sea el depósito más cercano y que sea asignable (o sea, factible)
            if (instance.costos[i][vendedor_promedio_minimo] < costo_minimo && capacidades_residuales[i] - instance.demandas[i][vendedor_promedio_minimo] >= 0.0) {
                // si verifica la condición se actualiza el depósito mínimo del vendedor de promedio mínimo y el costo asociado
                deposito_minimo = i;
                costo_minimo = instance.costos[i][vendedor_promedio_minimo];
            }
        }

        // si tras evaluar sobre todos los depósitos, se halla un depósito asignable i más cercano para el vendedor de promedio mínimo,
        // se toma la decisión de asignarlo dicho vendedor a ese depósito
        if (deposito_minimo != -1) {
            // concretamos la asignación
            asignaciones[deposito_minimo].push_back(vendedor_promedio_minimo);
            asignaciones_vendedores[vendedor_promedio_minimo] = deposito_minimo;

            // actualizamos las capacidades residuales, el costo acumulado y los promedios de los vendedores aún disponibles
            capacidades_residuales[deposito_minimo] = capacidades_residuales[deposito_minimo] - instance.demandas[deposito_minimo][vendedor_promedio_minimo];
            solucion.costo_total += instance.costos[deposito_minimo][vendedor_promedio_minimo];
            vendedores_disponibles[vendedor_promedio_minimo] = false;
            promedio_costo_vendedores = calcular_promedios(instance, capacidades_residuales, vendedores_disponibles); // se recalculan los promedios
        } else { // en caso contrario se lo cuenta al vendedor de promedio mínimo como un vendedor sin asignar
            solucion.vendedores_sin_asignar++;
            asignaciones_vendedores[vendedor_promedio_minimo] = -1;
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

std::vector<double> calcular_promedios(const GAPInstance &instance, const std::vector<double> &capacidades_residuales, const std::vector<bool> &vendedores_disponibles) {
    // los promedios empiezan siendo cotas máximas para aquellos vendedores no disponibles o donde no podamos calcular el promedio
    std::vector<double> promedios(instance.n, std::numeric_limits<float>::infinity());

    // para cada vendedor j disponible se calcula su promedio de costos
    for (int j=0; j<instance.n; j++) {
        if (vendedores_disponibles[j] == false) continue;
        double sum_total = 0.0;
        int cant = 0;
        for (int i=0; i<instance.m; i++) {
            if (instance.demandas[i][j] <= capacidades_residuales[i]) {
                sum_total += instance.costos[i][j];
                cant++;
            }
        }
        // siempre y cuando se pueda calcular el promedio para el vendedor j se actualiza en la lista de promedios
        if (cant != 0) {
            promedios[j] = sum_total/cant;
        }
    }
    return promedios;
}