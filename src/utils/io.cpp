#include "io.h"
#include <fstream>

void save_solution(
    const std::string& output,
    const std::string& input,
    const std::string& algoritmo,
    const Solution& solution,
    const GAPInstance& instance
){
    // siempre guardamos las salidas en la carpeta /output
    const std::string output_dir = "./output";
    const std::string output_file = output_dir + "/" + output;
    std::vector<std::vector<int>> asignaciones = solution.asignaciones;
    // iniciamos un flujo para escribir el archivo sobre la ruta output_file
    std::ofstream file(output_file);
    // escribimos en el archivo de salida los datos de salida y las asignaciones que resolvio el algoritmo
    file << "Instancia: " << input << "\n";
    file << "Algoritmo: " << algoritmo << "\n";
    file << "Costo total: " << solution.costo_total << "\n";
    file << "Solución parcial: " << (solution.parcial() ? "SÍ" : "NO") << "\n";
    file << "Cantidad de depósitos: " << instance.m << "\n";
    if (solution.parcial()) {
        file << "Cantidad de vendedores (sin asignar)/asignados: (" << solution.vendedores_sin_asignar << ")/" << instance.n << "\n";
    }
    for(int i=0; i<asignaciones.size(); i++){
        file << "Depósito ("<< i << "): ";
        for (int j=0; j<asignaciones[i].size(); j++){
            file << asignaciones[i][j] << " ";
        }
        file << "\n";
    }
}