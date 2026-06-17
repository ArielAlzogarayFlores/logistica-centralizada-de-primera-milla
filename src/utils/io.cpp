#include "io.h"
#include <fstream>

void save_solution(
    const std::string& output,
    const Solution& solution
){
    const std::string output_dir = "./output";
    const std::string output_file = output_dir + "/" + output;
    std::ofstream file(output_file);
    std::vector<std::vector<int>> asignaciones = solution.asignaciones;
    for(const auto& deposito : asignaciones){
        for(int vendedor : deposito){
            file << vendedor << " ";
        }
        file << "\n";
    }
}