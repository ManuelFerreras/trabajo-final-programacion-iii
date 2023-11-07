#include <iostream>
#include <functional>
#include <unordered_map>
#include <map>
#include "utils/csv/CSVReader.h"
#include "utils/deposit/DepositTree.h"
#include "utils/map/ArticlesMap.h"

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


std::unordered_map<std::string, std::function<void(const std::string &)>> routerDeArgumentos(
        std::unordered_map<std::string, Articulo> &mapaArticulos,
        std::vector<std::multimap<int, std::string>> &depositos,
        int &depositosTotales
) {
    // Definimos las acciones como funciones lambda.
    std::unordered_map<std::string, std::function<void(const std::string &)>> acciones = {
            {"total_art_dif", [&mapaArticulos](const std::string &param) {
                int cantidadArticulos = getTotalArticulosDiferentes(mapaArticulos);
                std::cout << "Cantidad de articulos diferentes: " << cantidadArticulos << std::endl;
            }},

            {"total_art",     [depositosTotales](const std::string &param) {
                std::cout << "Cantidad de articulos: " << depositosTotales << std::endl;
            }},


            {"min_stock",     [&depositos](const std::string &param) {
                int minStock = 0, deposito = 0;
                if (validarParametros(param, minStock, deposito)) {
                    if (deposito == 0) {
                        int totalArticulosFiltrados = mostrarArticulosConStockMenorOIgualA(depositos[0], minStock);
                        std::cout << "Cantidad de articulos totales con stock menor o igual a " << minStock << ": "
                                  << totalArticulosFiltrados << std::endl;
                    } else {
                        int totalArticulosFiltrados = mostrarArticulosConStockMenorOIgualA(depositos[deposito],
                                                                                           minStock);
                        std::cout << "Cantidad de articulos en el deposito #" << deposito
                                  << " con stock menor o igual a " << minStock << ": " << totalArticulosFiltrados
                                  << std::endl;
                    }
                }
            }},

            {"stock",         [&mapaArticulos](const std::string &param) {
                int deposito = 0;
                if (validarStock(param, mapaArticulos, deposito)) {
                    auto params = splitCSVLine(param);
                    if (deposito == 0) {
                        int stockTotal = getStockTotal(mapaArticulos, params[0]);
                        std::cout << "Stock total del articulo '" << params[0] << "': " << stockTotal << std::endl;
                    } else {
                        int stockTotal = getStockTotal(mapaArticulos, params[0], deposito);
                        std::cout << "Stock del articulo '" << params[0] << "' en el deposito #" << deposito << ": "
                                  << stockTotal << std::endl;
                    }
                }
            }},


            {"max_stock",     [&depositos](const std::string &param) {
                int maxStock = 0;
                if (validarParametros(param, maxStock, maxStock)) {
                    int totalArticulosFiltrados = mostrarArticulosConStockMayorOIgualA(depositos[0], maxStock);
                    std::cout << "Cantidad de articulos totales con stock mayor o igual a " << maxStock << ": "
                              << totalArticulosFiltrados << std::endl;
                }
            }}
    };

    return acciones;

}


int main(int argc, char *argv[]) {
    /*
     * Chequeamos que se haya ingresado una cantidad valida de argumentos.
     */
    if (argc < 3) {
        std::cerr << "Uso: 'path al ejecutable' 'argumento' 'path al csv'.csv" << std::endl;
        return 1;
    }

    /*
     * Leemos los argumentos ingresados.
     */
    std::string archivoCSV = argv[argc - 1];
    std::string arg = argv[argc - 2];

    /*
     * Procesamos la data del CSV.
     */
    std::vector<std::multimap<int, std::string>> depositos;
    int depositosTotales = 0;
    std::unordered_map<std::string, Articulo> mapaArticulos = leerCSV(archivoCSV, depositos, depositosTotales);

    /*
     * Procesamos el argumento ingresado.
     */
    std::unordered_map<std::string, std::function<void(const std::string &)>> acciones = routerDeArgumentos(
            mapaArticulos, depositos, depositosTotales);

    /*
     * Dividir el argumento para obtener la acción y el parámetro
     */
    size_t posicion = arg.find('[');
    std::string accion = (posicion != std::string::npos) ? arg.substr(0, posicion) : arg;
    std::string parametro = (posicion != std::string::npos) ? arg.substr(posicion + 1, arg.size() - posicion - 2) : "";

    /*
     * Ejecutar la acción correspondiente si existe en el mapa
     */
    if (acciones.find(accion) != acciones.end()) {
        acciones[accion](parametro);
    } else {
        std::cerr << "Argumento no reconocido." << std::endl;
        return 1; // Termina el programa con un código de error.
    }

    return 0;
}