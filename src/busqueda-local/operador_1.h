#ifndef SRC_OPERADOR_1_H
#define SRC_OPERADOR_1_H

#include "../utils/gap_instance.h"
#include "../utils/solution.h"

Solution operador_1(const GAPInstance& instance, double cmax);

bool swap_op(Solution& solucion, const GAPInstance& instance, int j1, int j2);

#endif
