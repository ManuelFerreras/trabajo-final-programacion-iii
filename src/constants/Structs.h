#ifndef TRABAJO_FINAL_PROGRAMACION_III_STRUCTS_H
#define TRABAJO_FINAL_PROGRAMACION_III_STRUCTS_H

#include <iostream>
#include <vector>

// Estructura para representar un Articulo.
struct Articulo {
    std::string grupo;
    std::string nombre;
    std::vector<int> stockPorDeposito; // Almacena el stock de cada depósito
    int stockTotal = 0; // Sumatoria del stock en todos los depósitos
};

#endif //TRABAJO_FINAL_PROGRAMACION_III_STRUCTS_H
