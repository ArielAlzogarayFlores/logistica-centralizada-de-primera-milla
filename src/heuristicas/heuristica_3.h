#ifndef TD5_TP2_LCDPM_HEURISTICA_3_H
#define TD5_TP2_LCDPM_HEURISTICA_3_H

#include "../utils/gap_instance.h"
#include "../utils/solution.h"
#include <vector>

Solution heuristica_3(const GAPInstance &instance, int cmax);

std::vector<float> calcular_promedios(const GAPInstance &instance, const std::vector<int>& capacidades_residuales, const std::vector<bool>& vendedores_disponibles);

#endif