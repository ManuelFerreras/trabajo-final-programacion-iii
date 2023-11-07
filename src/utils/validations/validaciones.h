#ifndef TRABAJO_FINAL_PROGRAMACION_III_VALIDACIONES_H
#define TRABAJO_FINAL_PROGRAMACION_III_VALIDACIONES_H

#include <iostream>
#include <functional>
#include <unordered_map>
#include "../csv/CSVReader.h"
#include "validaciones.h"

// Funciones de validación
bool validarParametros(const std::string &param, int &numStock, int &deposito);

bool validarCodigoBarras(const std::string &codigo, const std::unordered_map<std::string, Articulo> &mapaArticulos);

bool validarStock(const std::string &param, const std::unordered_map<std::string, Articulo> &mapaArticulos, int &deposito);


#endif //TRABAJO_FINAL_PROGRAMACION_III_VALIDACIONES_H
