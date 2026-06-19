#ifndef SRC_GRASP_H
#define SRC_GRASP_H

#include "../utils/solution.h"
#include "../utils/gap_instance.h"

Solution grasp (const GAPInstance &instance, double cmax, const int n_iteraciones, const double alpha);

Solution operador_grasp(const GAPInstance &instance, double cmax, const double alpha);

Solution greedy_grasp (const GAPInstance &instance, double cmax, const double alpha);

#endif
