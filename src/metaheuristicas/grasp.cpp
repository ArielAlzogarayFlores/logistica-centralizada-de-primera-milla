#include "grasp.h"
#include <algorithm>
#include <limits>
#include <random>
#include "../busqueda-local/operador_2.h"

Solution grasp(const GAPInstance &instance, double cmax, const int n_iteraciones, const double alpha) {
    // creamos una solución sin inicializar
    Solution solucion;

    // queremos buscar la solución de costo mínimo
    // luego, inicialmente el costo mínimo es infinito
    double costo_minimo = std::numeric_limits<double>::infinity();

    // buscamos la solución de costo mínimo entre n iteraciones
    for (int k = 0; k < n_iteraciones; k++) {
        // donde la solucion k es hallada mediante el operador relocate
        // que a su vez consigue una solución factible inicial con un greedy randomizado
        Solution solucion_k = operador_grasp(instance, cmax, alpha);
        if (solucion_k.costo_total < costo_minimo) {
            solucion = solucion_k;
            costo_minimo = solucion_k.costo_total;
        }
    }
    return solucion;
}

Solution operador_grasp(const GAPInstance &instance, double cmax, const double alpha) {
    // alpha > 1.0

    // generemos una solución factible
    Solution solucion = greedy_grasp(instance, cmax, alpha);

    // mientras podamos mejorar la solución actual
    bool solucion_mejorable = true;
    while (solucion_mejorable) {
        // buscamos un relocate que resulte en mejora (la primera mejora)
        bool mejora_hallada = false;

        for (int j = 0; j < instance.n && not mejora_hallada; j++) {
            for (int i = 0; i < instance.m && not mejora_hallada; i++) {
                // debemos hacer el relocate sobre un depósito distinto al que ya se encuentra el vendedor
                if (solucion.asignaciones_vendedores[j] == i || solucion.asignaciones_vendedores[j] == -1) continue;

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

Solution greedy_grasp(const GAPInstance &instance, double cmax, const double alpha) {
    // alpha > 1.0

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

    // creamos un vector con los vendedores pero en un orden aleatorio
    std::vector<int> vendedores_randomizados(instance.n);

    // creamos un objeto para randomizar de forma previsible (semilla)
    std::random_device rd;

    // usamos el siguiente algoritmo para randomizar el objeto
    std::mt19937 gen(rd());

    // creamos el vector con los vendedores
    for (int j=0; j < instance.n; j++) {
        vendedores_randomizados[j] = j;
    }

    // randomizamos el vector
    std::shuffle(vendedores_randomizados.begin(), vendedores_randomizados.end(), gen);

    // por cada vendedor j (en orden aleatorio) buscamos el depósito asignable i más cercano
    for (int j : vendedores_randomizados) {
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
        // se toma la decisión de buscar los depósitos más cercanos (con el mínimo como cota inferior) y
        // asignar j a uno de esos depósitos de forma aleatoria
        if (deposito_minimo != -1) {
            std::vector<int> depositos_cercanos = {deposito_minimo};
            for (int i = 0; i < instance.m; i++) {
                // verificamos que sea un depósito cercano (definido por alpha) y que sea asignable (o sea, factible)
                if (i != deposito_minimo && instance.costos[i][j] < costo_minimo * alpha && capacidades_residuales[i] - instance.demandas[i][j] >= 0.0) {
                    depositos_cercanos.push_back(i);
                }
            }
            // elegimos aleatoriamente uno de los depósitos para asignar j
            // dentro de la lista de los depósitos más cercanos a dicho vendedor
            std::uniform_int_distribution<int> dist(0, depositos_cercanos.size() - 1);
            int pos_deposito_elegido = dist(gen);
            int deposito_elegido = depositos_cercanos[pos_deposito_elegido];

            // concretamos la asignación
            asignaciones[deposito_elegido].push_back(j);
            asignaciones_vendedores[j] = deposito_elegido;

            // actualizamos las capacidades residuales y el costo acumulado
            capacidades_residuales[deposito_elegido] -= instance.demandas[deposito_elegido][j];
            solucion.costo_total += instance.costos[deposito_elegido][j];

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
