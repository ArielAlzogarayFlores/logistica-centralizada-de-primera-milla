#include "operador_1.h"
#include "../heuristicas/heuristica_2.h"

Solution operador_1(const GAPInstance& instance, double cmax) {
    // generemos una solución factible
    Solution solucion = heuristica_2(instance, cmax);

    // mientras podamos mejorar la solución actual
    bool solucion_mejorable = true;
    while (solucion_mejorable) {
        // buscamos un swap que resulte en mejora (la primera mejora)
        bool mejora_hallada = false;

        for (int j1 = 0; j1 < instance.n && not mejora_hallada; j1++) {
            // deben ser vendedores distintos
            for (int j2 = j1+1; j2 < instance.n && not mejora_hallada; j2++) {
                // deben ser vendedores asignados a depósitos distintos
                if (solucion.asignaciones_vendedores[j1] == solucion.asignaciones_vendedores[j2]
                    || solucion.asignaciones_vendedores[j1] == -1
                    || solucion.asignaciones_vendedores[j2] == -1) continue;
                // actualizamos la solución siempre que el swap resulte en una reducción de costos factible
                if (swap_op(solucion, instance, j1, j2)) {
                    mejora_hallada = true;
                }
            }
        }

        // si no se encontro una mejora
        if (not mejora_hallada) solucion_mejorable = false;
    }
    return solucion;
}

bool swap_op(Solution &solucion, const GAPInstance& instance, int j1, int j2) {
    const int i1 = solucion.asignaciones_vendedores[j1];
    const int i2 = solucion.asignaciones_vendedores[j2];

    // buscamos las posiciones de j1 y j2 en las asignaciones dentro de sus respectivos depósitos i1 e i2
    int pos_j1 = -1;
    int pos_j2 = -1;

    // posicion de j1
    for (int j=0; j<solucion.asignaciones[i1].size(); j++) {
        if (solucion.asignaciones[i1][j] == j1) {
            pos_j1 = j;
            break;
        }
    }

    // posicion de j2
    for (int j=0; j<solucion.asignaciones[i2].size(); j++) {
        if (solucion.asignaciones[i2][j] == j2) {
            pos_j2 = j;
            break;
        }
    }

    // si no encontramos a los vendedores en sus depósitos la operación de swap no se puede realizar
    if (pos_j1 == -1 || pos_j2 == -1) return false;

    // verificamos condición de optimalidad y factibilidad
    const bool cond_optimalidad = instance.costos[i2][j1] + instance.costos[i1][j2] < instance.costos[i1][j1] + instance.costos[i2][j2];
    const bool cond_factibilidad = instance.demandas[i2][j1] <= solucion.capacidades_residuales[i2] + instance.demandas[i2][j2] &&
                                   instance.demandas[i1][j2] <= solucion.capacidades_residuales[i1] + instance.demandas[i1][j1];

    // si se verifican las condiciones concretamos el swap y actualizamos la solución
    if (cond_optimalidad && cond_factibilidad) {
        // operación de swap
        solucion.asignaciones[i1][pos_j1] = j2;
        solucion.asignaciones[i2][pos_j2] = j1;

        // actualización del resto de la solución (perspectiva de vendedores y capacidades residuales)
        solucion.asignaciones_vendedores[j1] = i2;
        solucion.asignaciones_vendedores[j2] = i1;
        solucion.capacidades_residuales[i1] += instance.demandas[i1][j1] - instance.demandas[i1][j2];
        solucion.capacidades_residuales[i2] += instance.demandas[i2][j2] - instance.demandas[i2][j1];
        solucion.costo_total -= instance.costos[i1][j1] + instance.costos[i2][j2]; // quitamos costo viejo
        solucion.costo_total += instance.costos[i2][j1] + instance.costos[i1][j2]; // agregamos costo nuevo

        // la operación de swap es factible y representa una mejora
        return true;
    }

    // la operación de swap no es factible o no representa una mejora
    return false;
}
