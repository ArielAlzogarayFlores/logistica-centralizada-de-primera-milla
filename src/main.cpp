#include <iostream>
#include <vector>

#include "utils/gap_instance.h"
#include "utils/io.h"
#include "utils/algorithm_runner.h"

int main(int argc,char** argv){
    if(argc < 4){
        std::cout
            << "Uso:\n"
            << "./gap_simulator "
            << "<input> "
            << "<output> "
            << "<algoritmo>\n";
        return 1;
    }

    try{
        std::string input_file=argv[1];
        std::string output_file= argv[2];
        std::string algorithm=argv[3];

        std::cout
            << "Leyendo "
            << input_file
            << "\n";
        GAPInstance instance = read_instance(input_file);
        std::vector<int> N(instance.n);
        std::vector<int> M(instance.m);
        for(int i=0; i<instance.n; i++) N[i]=i;
        for(int i=0; i<instance.m; i++) M[i]=i;
        int cmax = c_max(N,M,instance.costos);
        auto solution = run_algorithm(algorithm,instance,cmax);
        save_solution(output_file, solution);

        std::cout
            << "\nInstancia cargada\n"
            << "Depositos: "
            << instance.m
            << "\nVendedores: "
            << instance.n
            << "\nc_max: "
            << cmax
            << "\nOutput: ./output/"
            << output_file
            << "\n";
    }

    catch(std::exception& e){
        std::cerr
            << "ERROR: "
            << e.what()
            << "\n";
        return 1;
    }
    return 0;
}