#include "gap_instance.h"

#include <fstream>
#include <stdexcept>

GAPInstance read_instance(const std::string& filename){
    std::ifstream file(filename);
    if(!file.is_open()){
        throw std::runtime_error("No se pudo abrir el archivo.");
    }
    GAPInstance instance;
    file >> instance.m >> instance.n;
    instance.costos.resize(
        instance.m,
        std::vector<int>(instance.n)
    );
    instance.recursos.resize(
        instance.m,
        std::vector<int>(instance.n)
    );
    instance.capacidades.resize(instance.m);

    // costos
    for(int i=0;i<instance.m;i++){
        for(int j=0;j<instance.n;j++){
            file >> instance.costos[i][j];
        }
    }

    // recursos
    for(int i=0;i<instance.m;i++){
        for(int j=0;j<instance.n;j++){
            file >> instance.recursos[i][j];
        }
    }

    // capacidades
    for(int i=0;i<instance.m;i++){
        file >> instance.capacidades[i];
    }

    return instance;
}


int c_max(
    const std::vector<int>& N,
    const std::vector<int>& M,
    const std::vector<std::vector<int>>& costos
){
    int res = 0;
    for(int i=0;i<M.size();i++){
        for(int j=0;j<N.size();j++){
            if(costos[i][j] > res){
                res = costos[i][j];
            }
        }
    }
    return res;
}