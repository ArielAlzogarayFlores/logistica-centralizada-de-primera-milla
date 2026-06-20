#include "algorithm_runner.h"
#include "../heuristicas/heuristica_1.h"
#include "../heuristicas/heuristica_3.h"
#include "../heuristicas/heuristica_2.h"
#include "../heuristicas/heuristica_4.h"
#include "../busqueda-local/operador_1.h"
#include "../busqueda-local/operador_2.h"
#include "../metaheuristicas/grasp.h"
#include <stdexcept>

Solution run_algorithm(
    const std::string& algorithm,
    const GAPInstance& instance,
    double cmax
){
    if(algorithm=="heuristica_1"){
        return heuristica_1(instance,cmax);
    }
    if(algorithm=="heuristica_2"){
        return heuristica_2(instance,cmax);
    }
    if(algorithm=="heuristica_3"){
        return heuristica_3(instance,cmax);
    }
    if(algorithm=="heuristica_4"){
        return heuristica_4(instance,cmax);
    }
    if(algorithm=="operador_1"){
        return operador_1(instance,cmax);
    }
    if(algorithm=="operador_2"){
        return operador_2(instance,cmax);
    }
    if(algorithm=="grasp"){
        return grasp(instance,cmax, 20, 0.75);
    }
    throw std::runtime_error(
        "Algoritmo inexistente"
    );
}
