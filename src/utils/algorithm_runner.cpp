#include "algorithm_runner.h"
#include "../heuristicas/heuristica_1.h"
#include "../heuristicas/heuristica_2.h"
#include "../heuristicas/heuristica_5.h"
#include "../busqueda-local/operador_1.h"
#include <stdexcept>

Solution run_algorithm(
    const std::string& algorithm,
    const GAPInstance& instance,
    int cmax
){
    if(algorithm=="heuristica_1"){
        return heuristica_1(instance,cmax);
    }
    if(algorithm=="heuristica_2"){
        return heuristica_2(instance,cmax);
    }
    if(algorithm=="heuristica_5"){
        return heuristica_5(instance,cmax);
    }
    if(algorithm=="operador_1"){
        return operador_1(instance,cmax);
    }
    if(algorithm=="meta1"){
        // return meta(instance,cmax);
    }
    throw std::runtime_error(
        "Algoritmo inexistente"
    );
}
