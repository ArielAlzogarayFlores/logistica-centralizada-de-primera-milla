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
    file << "Costo total: " << solution.costo_total << "\n";
    file << "Solución parcial: " << (solution.parcial() ? "SÍ" : "NO") << "\n";
    if (solution.parcial()) {
        file << "Cantidad de vendedores sin asignar:" << solution.vendedores_sin_asignar << "\n";
    }
    for(int i=0; i<asignaciones.size(); i++){
        file << "Depósito ("<< i << "): ";
        for (int j=0; j<asignaciones[i].size(); j++){
            file << asignaciones[i][j] << " ";
        }
        file << "\n";
    }
}