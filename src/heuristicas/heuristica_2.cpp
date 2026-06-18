#include <limits.h>
#include "heuristica_2.h"
#include <vector>

Solution heuristica_2(const GAPInstance &instance, int cmax)
{
    Solution solucion;
    solucion.vendedores_sin_asignar = 0;
    solucion.costo_total = 0;
    std::vector<std::vector<int>> asignaciones(instance.m);
    std::vector<int> capacidades_residuales = instance.capacidades;
    std::vector<int> marcado(instance.n, 0);

    int cota_superior = instance.n * instance.m;
    int contador = 0;

    while (contador <= cota_superior)
    {
        for (int i = 0; i < instance.m; i++)
        {
            int n_min = -1;
            int c_min = INT_MAX;
            for (int j = 0; j < instance.n; j++)
            {
                if (c_min > instance.costos[i][j] && capacidades_residuales[i] >= instance.demandas[i][j] && marcado[j] == 0)
                {
                    n_min = j;
                    c_min = instance.costos[i][j];
                }
            }
            if (n_min != -1)
            {
                asignaciones[i].push_back(n_min);
                capacidades_residuales[i] = capacidades_residuales[i] - instance.demandas[i][n_min];
                marcado[n_min] = 1;
            }
        }
        contador += 1;
    }

    for (int j = 0; j < instance.n; j++)
    {
        if (marcado[j] == 0)
        {
            solucion.vendedores_sin_asignar += 1;
        }
    }

    solucion.asignaciones = asignaciones;
    solucion.costo_total += (3 * cmax) * solucion.vendedores_sin_asignar;
    return solucion;
}