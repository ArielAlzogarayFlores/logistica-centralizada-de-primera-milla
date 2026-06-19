#ifndef TD5_TP2_LCDPM_HEURISTICA_3_H
#define TD5_TP2_LCDPM_HEURISTICA_3_H

#include "../utils/gap_instance.h"
#include "../utils/solution.h"
#include <vector>

Solution heuristica_3(const GAPInstance &instance, double cmax);

std::vector<double> calcular_promedios(const GAPInstance &instance, const std::vector<double>& capacidades_residuales, const std::vector<bool>& vendedores_disponibles);

#endif