#ifndef SRC_GRASP_H
#define SRC_GRASP_H

#include "../utils/solution.h"
#include "../utils/gap_instance.h"
#include <random>

Solution grasp (const GAPInstance &instance, double cmax, int n_iteraciones, double alpha);

Solution operador_grasp(const GAPInstance &instance, double cmax, double alpha, std::mt19937& generador);

Solution greedy_grasp (const GAPInstance &instance, double cmax, double alpha, std::mt19937& generador);

#endif
