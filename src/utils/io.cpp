#include "io.h"

#include <fstream>

void save_solution(
    const std::string& output,
    const std::vector<std::vector<int>>& solution
){
    const std::string output_dir = "./output";
    const std::string output_file = output_dir + "/" + output;
    std::ofstream file(output_file);
    for(const auto& deposito : solution){
        for(int vendedor : deposito){
            file << vendedor << " ";
        }
        file << "\n";
    }
}