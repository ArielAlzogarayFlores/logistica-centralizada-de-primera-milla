#include "heuristica_4.h"
#include <vector>
#include <map>
#include <utility>

Solution heuristica_4(const GAPInstance &instance, int cmax) {
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

    // creamos un map que almacena el ratio costo-demanda asociado a cada par depósito-vendedor
    std::map<std::pair<int, int>, float> ratios_costo_demanda;
    for (int j = 0; j < instance.n; j++) {
        for (int i = 0; i < instance.m; i++) {
            // asumo que las demandas son siempre no nulas
            ratios_costo_demanda[{i,j}] = static_cast<float>(instance.costos[i][j]) / instance.demandas[i][j];
        }
    }

    // creamos un vector de pares depósito-vendedor donde ordenemos las claves del map de menor a mayor ratio (orden en el que intentaremos realizar las asignaciones)
    std::vector<std::pair<int,int>> orden_asignacion;
    for (int j = 0; j < instance.n; j++) {
        for (int i = 0; i < instance.m; i++) {
            // creamos un par depósito i, vendedor j
            std::pair<int,int> par = {i, j};

            // lo añadimos al vector de orden_asignacion
            orden_asignacion.push_back(par);

            // siempre que sea posible hacemos swap para mantener ordenado el vector construido hasta el momento
            int c = orden_asignacion.size() - 1;
            while (c > 0 && ratios_costo_demanda[orden_asignacion[c]] < ratios_costo_demanda[orden_asignacion[c - 1]]) {
                std::swap(orden_asignacion[c], orden_asignacion[c - 1]);
                c--;
            }
        }
    }

    // concretamos las asignaciones según el orden de ratio
    for (int k=0; k<orden_asignacion.size(); k++) {
        if (vendedores_disponibles[orden_asignacion[k].second] &&
            capacidades_residuales[orden_asignacion[k].first] - instance.demandas[orden_asignacion[k].first][orden_asignacion[k].second] >= 0) {

            // concretamos la asignación
            asignaciones[orden_asignacion[k].first].push_back(orden_asignacion[k].second);
            asignaciones_vendedores[orden_asignacion[k].second] = orden_asignacion[k].first;

            // actualizamos las capacidades residuales, el costo acumulado y ponemos al vendedor j como no disponible
            capacidades_residuales[orden_asignacion[k].first] = capacidades_residuales[orden_asignacion[k].first] - instance.demandas[orden_asignacion[k].first][orden_asignacion[k].second];
            solucion.costo_total += instance.costos[orden_asignacion[k].first][orden_asignacion[k].second];
            vendedores_disponibles[orden_asignacion[k].second] = false;
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
