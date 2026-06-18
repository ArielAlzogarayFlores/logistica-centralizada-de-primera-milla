#include <limits.h>
#include "heuristica_4.h"
#include <vector>
#include <map>
#include <utility>

Solution heuristica_4(const GAPInstance &instance, int cmax)
{
    Solution solucion;
    solucion.vendedores_sin_asignar = 0;
    solucion.costo_total = 0;
    std::vector<int> promedios;
    std::vector<std::vector<int>> asignaciones(instance.m);
    std::vector<int> capacidades_residuales = instance.capacidades;
    std::vector<int> marcado(instance.n, 0);
    std::map<std::pair<int, int>, int> ratios;
    std::vector<std::pair<int, int>> pares;

    for (int j = 0; j < instance.n; j++)
    {
        for (int i = 0; i < instance.m; i++)
        {
            ratios[{j, i}] = instance.costos[i][j] / instance.demandas[i][j];
        }
    }

    for (int j = 0; j < instance.n; j++)
    {
        for (int i = 0; i < instance.m; i++)
        {
            std::pair<int, int> par = {j, i};
            pares.push_back(par);
            if (pares.size() > 1)
            {
                int c = pares.size() - 1;
                int k = c - 1;
                while (k >= 0)
                {
                    if (ratios[pares[c]] < ratios[pares[k]])
                    {
                        std::pair<int, int> aux = pares[k];
                        pares[k] = pares[c];
                        pares[c] = aux;
                        c -= 1;
                        k -= 1;
                    }
                    else
                    {
                        k = -100;
                    }
                }
            }
        }
    }

    int cantidad_pares = pares.size();

    for (int ji = 0; ji < cantidad_pares; ji++)
    {
        if (marcado[pares[ji].first] == 0 && capacidades_residuales[pares[ji].second] >= instance.demandas[pares[ji].second][pares[ji].first])
        {
            marcado[pares[ji].first] = 1;
            asignaciones[pares[ji].second].push_back(marcado[pares[ji].first]);
            capacidades_residuales[pares[ji].second] = capacidades_residuales[pares[ji].second] - instance.demandas[pares[ji].second][pares[ji].first];
        }
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
