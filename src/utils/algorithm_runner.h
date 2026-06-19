#ifndef RUNNER_H
#define RUNNER_H

#include "gap_instance.h"
#include "solution.h"

Solution run_algorithm(
    const std::string& algorithm,
    const GAPInstance& instance,
    double cmax
);

#endif