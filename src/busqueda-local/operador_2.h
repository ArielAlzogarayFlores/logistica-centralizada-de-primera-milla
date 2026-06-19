#ifndef SRC_OPERADOR_2_H
#define SRC_OPERADOR_2_H

#include "../utils/solution.h"
#include "../utils/gap_instance.h"

Solution operador_2(const GAPInstance& instance, double cmax);

bool relocate_op (Solution &solucion, const GAPInstance& instance, int i, int j);

#endif
