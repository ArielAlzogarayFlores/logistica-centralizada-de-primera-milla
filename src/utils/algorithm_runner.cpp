#include "algorithm_runner.h"

#include <stdexcept>

// incluir algoritmos reales
std::vector<std::vector<int>> run_algorithm(
    const std::string& algorithm,
    const GAPInstance& instance,
    int cmax
){
    if(algorithm=="heuristica1"){
        // return heuristica1(instance,cmax);
    }
    if(algorithm=="local1"){
        // return local_search(instance,cmax);
    }
    if(algorithm=="meta1"){
        // return meta(instance,cmax);
    }
    throw std::runtime_error(
        "Algoritmo inexistente"
    );
}