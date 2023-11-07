
#include <iostream>
#include <functional>
#include <unordered_map>
#include "../csv/CSVReader.h"
#include "validaciones.h"

// Funciones de validación
bool validarParametros(const std::string &param, int &numStock, int &deposito) {
    auto params = splitCSVLine(param);
    if (params.size() == 1) {
        try {
            numStock = std::stoi(params[0]);
        } catch (const std::invalid_argument &) {
            std::cerr << "Error: El valor n no es un numero valido." << std::endl;
            return false;
        }
        if (numStock < 0) {
            std::cerr << "Error: El valor n debe ser mayor que cero." << std::endl;
            return false;
        }
    } else if (params.size() == 2) {
        try {
            numStock = std::stoi(params[0]);
            deposito = std::stoi(params[1]);
        } catch (const std::invalid_argument &) {
            std::cerr << "Error: Los valores n o deposito no son numeros validos." << std::endl;
            return false;
        }
        if (numStock < 0 || deposito < 0) {
            std::cerr << "Error: Los valores n y deposito deben ser mayores que cero." << std::endl;
            return false;
        }
    } else {
        std::cerr << "Error: Formato incorrecto." << std::endl;
        return false;
    }
    return true;
}

bool validarCodigoBarras(const std::string &codigo, const std::unordered_map<std::string, Articulo> &mapaArticulos) {
    if (mapaArticulos.find(codigo) == mapaArticulos.end()) {
        std::cerr << "Error: El codigo de barras no existe en el mapa de articulos." << std::endl;
        return false;
    }
    return true;
}

bool validarStock(const std::string &param, const std::unordered_map<std::string, Articulo> &mapaArticulos, int &deposito) {
    auto params = splitCSVLine(param);
    if (params.size() == 1) {
        if (validarCodigoBarras(params[0], mapaArticulos)) {
            return true;
        }
    } else if (params.size() == 2) {
        if (validarParametros(params[1], deposito, deposito) && validarCodigoBarras(params[0], mapaArticulos)) {
            return true;
        }
    }
    std::cerr << "Error: Formato incorrecto." << std::endl;
    return false;
}
