#include "gap_instance.h"
#include <fstream>
#include <stdexcept>

GAPInstance read_instance(const std::string& filename){
    // iniciamos un flujo para escribir el archivo sobre la ruta filename
    std::ifstream file(filename);
    if(!file.is_open()){
        throw std::runtime_error("No se pudo abrir el archivo.");
    }
    // creamos una instancia de GAP a partir del parsing sobre el archivo leído
    GAPInstance instance;
    file >> instance.m >> instance.n;
    instance.costos.resize(
        instance.m,
        std::vector<double>(instance.n)
    );
    instance.demandas.resize(
        instance.m,
        std::vector<double>(instance.n)
    );
    instance.capacidades.resize(instance.m);

    // costos
    for(int i=0;i<instance.m;i++){
        for(int j=0;j<instance.n;j++){
            file >> instance.costos[i][j];
        }
    }

    // demandas
    for(int i=0;i<instance.m;i++){
        for(int j=0;j<instance.n;j++){
            file >> instance.demandas[i][j];
        }
    }

    // capacidades
    for(int i=0;i<instance.m;i++){
        file >> instance.capacidades[i];
    }

    // por si hay un error de lectura
    if (file.fail()) {
        throw std::runtime_error("Error parseando instancia");
    }

    return instance;
}


double costo_max(
    const std::vector<int>& N,
    const std::vector<int>& M,
    const std::vector<std::vector<double>>& costos
){
    double res = 0.0;
    for(int i=0;i<M.size();i++){
        for(int j=0;j<N.size();j++){
            if(costos[i][j] > res){
                res = costos[i][j];
            }
        }
    }
    return res;
}