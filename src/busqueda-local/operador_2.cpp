#include "operador_2.h"
#include "../heuristicas/heuristica_2.h"

Solution operador_2(const GAPInstance& instance, int cmax) {
    // generemos una solución factible
    Solution solucion = heuristica_2(instance, cmax);

    // mientras podamos mejorar la solución actual
    bool solucion_mejorable = true;
    while (solucion_mejorable) {
        // buscamos un relocate que resulte en mejora (la primera mejora)
        bool mejora_hallada = false;

        for (int j = 0; j < instance.n && not mejora_hallada; j++) {
            for (int i = 0; i < instance.m && not mejora_hallada; i++) {
                // debemos hacer el relocate sobre un depósito distinto al que ya se encuentra el vendedor
                if (solucion.asignaciones_vendedores[j] == i) continue;

                // actualizamos la solución siempre que el relocate resulte en una reducción de costos factible
                if (relocate_op(solucion, instance, i, j)) {
                    mejora_hallada = true;
                }
            }
        }

        // si no se encontro una mejora
        if (not mejora_hallada) solucion_mejorable = false;
    }
    return solucion;
}

bool relocate_op(Solution &solucion, const GAPInstance &instance, int i, int j) {
    int deposito_j = solucion.asignaciones_vendedores[j];

    // busco la posición del vendedor j dentro de las asignaciones del depósito actual
    int pos_j = -1;
    for (int k = 0; k < solucion.asignaciones[deposito_j].size(); k++) {
        if (solucion.asignaciones[deposito_j][k] == j) {
            pos_j = k;
            break;
        }
    }

    // si no encontramos la posición de j respecto a su depósito la operación de relocate no se puede realizar
    if (pos_j == -1) return false;

    // verificamos condicion de optimalidad y factibilidad
    const bool cond_optimalidad = instance.costos[i][j] < instance.costos[deposito_j][j];
    const bool cond_factibilidad = instance.demandas[i][j] <= solucion.capacidades_residuales[i];

    // si se verifican las condiciones concretamos el relocate y actualizamos la solución
    if (cond_optimalidad && cond_factibilidad) {
        // operación de relocate
        solucion.asignaciones[deposito_j].erase(solucion.asignaciones[deposito_j].begin() + pos_j);
        solucion.asignaciones[i].push_back(j);

        // actualización del resto de la solución (perspectiva de vendedores y capacidades residuales)
        solucion.asignaciones_vendedores[j] = i;
        solucion.capacidades_residuales[deposito_j] += instance.demandas[deposito_j][j];
        solucion.capacidades_residuales[i] -= instance.demandas[i][j];
        solucion.costo_total -= instance.costos[deposito_j][j]; // quitamos costo viejo
        solucion.costo_total += instance.costos[i][j];  // agregamos costo nuevo

        // la operación de relocate es factible y representa una mejora
        return true;
    }
    // la operación de relocate no es factible o no representa una mejora
    return false;
}
