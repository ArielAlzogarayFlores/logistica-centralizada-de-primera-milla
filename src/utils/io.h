#ifndef IO_H
#define IO_H

#include <string>
#include "gap_instance.h"
#include "solution.h"

void save_solution(
    const std::string& output,
    const std::string& input,
    const std::string& algoritmo,
    const Solution& solution,
    const GAPInstance& instance,
    const double& time
);

#endif