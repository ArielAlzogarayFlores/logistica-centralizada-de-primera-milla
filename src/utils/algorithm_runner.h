#ifndef RUNNER_H
#define RUNNER_H

#include "gap_instance.h"

#include <vector>
#include <string>

std::vector<std::vector<int>> run_algorithm(
    const std::string& algorithm,
    const GAPInstance& instance,
    int cmax
);

#endif