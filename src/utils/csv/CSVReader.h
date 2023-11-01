#ifndef TRABAJO_FINAL_PROGRAMACION_III_CSVREADER_H
#define TRABAJO_FINAL_PROGRAMACION_III_CSVREADER_H

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <map>
#include "../../constants/Structs.h"


/*
 * Función para dividir una línea de CSV en campos, teniendo en cuenta las comillas.
 */
std::vector<std::string> splitCSVLine(const std::string& linea);

/*
 * Función para leer un archivo CSV y devolver un unordered_map con los artículos y un vector de depósitos.
 */
std::unordered_map<std::string, Articulo> leerCSV(const std::string& archivo, std::vector<std::multimap<int, std::string>>& depositos);

#endif //TRABAJO_FINAL_PROGRAMACION_III_CSVREADER_H
