#include <limits.h>
#include "heuristica_3.h"
#include <vector>

Solution heuristica_3(const GAPInstance &instance, int cmax)
{

    Solution solucion;
    solucion.vendedores_sin_asignar = 0;
    solucion.costo_total = 0;
    std::vector<int> promedios;
    std::vector<std::vector<int>> asignaciones(instance.m);
    std::vector<int> capacidades_residuales = instance.capacidades;
    std::vector<int> marcado(instance.n, 0);
    for (int j = 0; j < instance.n; j++)
    {
        float prom_j = 0;
        int a = 0;
        for (int i = 0; i < instance.m; i++)
        {
            if (capacidades_residuales[i] >= instance.demandas[i][j])
            {
                prom_j += instance.costos[i][j];
                a += 1;
            }
        }
        if (a = 0)
        {
            promedios.push_back(prom_j);
        }
        else
        {
            prom_j = prom_j / a;
            promedios.push_back(prom_j);
        }
    }

    int j = 0;

    while (j < instance.n)
    {
        int min_prom = INT_MAX;
        int pos_min = -1;
        for (int k = 0; k < instance.n; k++)
        {
            if (promedios[k] < min_prom && marcado[k] == 0)
            {
                min_prom = promedios[k];
                pos_min = k;
            }
        }

        int m_min = -1;
        int c_min = INT_MAX;
        for (int i = 0; i < instance.m; i++)
        {
            if (c_min > instance.costos[i][pos_min] && capacidades_residuales[i] >= instance.demandas[i][pos_min])
            {
                m_min = i;
                c_min = instance.costos[i][pos_min];
            }
        }
        if (m_min != -1)
        {
            asignaciones[m_min].push_back(pos_min);
            capacidades_residuales[m_min] = capacidades_residuales[m_min] - instance.demandas[m_min][pos_min];
        }
        else
        {
            solucion.vendedores_sin_asignar += 1;
        }
        marcado[pos_min] = 1;
        j += 1;

        for (int c = 0; c < instance.n; c++)
        {
            if (marcado[c] == 0)
            {
                float prom_c = 0;
                int a = 0;
                for (int i = 0; i < instance.m; i++)
                {
                    if (capacidades_residuales[i] >= instance.demandas[i][c])
                    {
                        prom_c += instance.costos[i][c];
                        a += 1;
                    }
                }
                if (a == 0)
                {
                    prom_c = 0;
                }
                else
                {
                    prom_c = prom_c / a;
                }
                promedios[c] = prom_c;
            }
        }
        solucion.asignaciones = asignaciones;
        solucion.costo_total += (3 * cmax) * solucion.vendedores_sin_asignar;
    }

    return solucion;
}