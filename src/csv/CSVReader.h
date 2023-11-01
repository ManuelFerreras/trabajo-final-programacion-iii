#ifndef TRABAJO_FINAL_PROGRAMACION_III_CSVREADER_H
#define TRABAJO_FINAL_PROGRAMACION_III_CSVREADER_H

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <map>

// Estructura para representar un Articulo.
struct Articulo {
    std::string grupo;
    std::string nombre;
    std::vector<int> stockPorDeposito; // Almacena el stock de cada depósito
    int stockTotal = 0; // Sumatoria del stock en todos los depósitos
};

// Función para dividir una línea de CSV en campos, teniendo en cuenta las comillas.
std::vector<std::string> splitCSVLine(const std::string& linea);

// Función para leer un archivo CSV y devolver un unordered_map con los artículos y un vector de depósitos.
std::unordered_map<std::string, Articulo> leerCSV(const std::string& archivo, std::vector<std::multimap<int, std::string>>& depositos);

#endif //TRABAJO_FINAL_PROGRAMACION_III_CSVREADER_H
