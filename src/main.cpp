#include <iostream>
#include <functional>
#include <unordered_map>
#include <map>
#include "utils/csv/CSVReader.h"
#include "utils/deposit/DepositTree.h"
#include "utils/map/ArticlesMap.h"

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
                return;
            }},

            {"total_art",     [depositosTotales](const std::string &param) {
                std::cout << "Cantidad de articulos: " << depositosTotales << std::endl;
                return;
            }},

            /*  {"min_stock", [&depositos](const std::string& param) {
                auto params = splitCSVLine(param);
                if (params.size() == 1) {
                  int minStock = std::stoi(params[0]);
                  int totalArticulosFiltrados = mostrarArticulosConStockMenorOIgualA(depositos[0], minStock);
                  std::cout << "Cantidad de articulos totales con stock menor o igual a " << minStock << ": " << totalArticulosFiltrados << std::endl;
                }
                else {
                  int minStock = std::stoi(params[0]);
                  int deposito = std::stoi(params[1]);
                  int totalArticulosFiltrados = mostrarArticulosConStockMenorOIgualA(depositos[deposito], minStock);
                  std::cout << "Cantidad de articulos en el deposito #" << deposito << " con stock menor o igual a " << minStock << ": " << totalArticulosFiltrados << std::endl;
                }
              }},*/

            {"min_stock",     [&depositos](const std::string &param) {
                auto params = splitCSVLine(param);
                if (params.size() == 1) {
                    int minStock;
                    try {
                        minStock = std::stoi(params[0]);
                    } catch (const std::invalid_argument &) {
                        std::cerr << "Error: El valor n no es un número válido." << std::endl;
                        return;
                    }
                    if (minStock < 0) {
                        std::cerr << "Error: El valor n debe ser mayor que cero." << std::endl;
                        return;
                    }
                    int totalArticulosFiltrados = mostrarArticulosConStockMenorOIgualA(depositos[0], minStock);
                    std::cout << "Cantidad de artículos totales con stock menor o igual a " << minStock << ": "
                              << totalArticulosFiltrados << std::endl;
                } else {
                    // Validar el número de argumentos y el valor del depósito
                    if (params.size() != 2) {
                        std::cerr << "Error: Formato incorrecto." << std::endl;
                        return;
                    }
                    int minStock, deposito;
                    try {
                        minStock = std::stoi(params[0]);
                        deposito = std::stoi(params[1]);
                    } catch (const std::invalid_argument &) {
                        std::cerr << "Error: Los valores n o depósito no son números válidos." << std::endl;
                        return;
                    }
                    if (minStock < 0 || deposito < 0) {
                        std::cerr << "Error: Los valores n y depósito deben ser mayores que cero." << std::endl;
                        return;
                    }
                    int totalArticulosFiltrados = mostrarArticulosConStockMenorOIgualA(depositos[deposito], minStock);
                    std::cout << "Cantidad de artículos en el depósito #" << deposito << " con stock menor o igual a "
                              << minStock << ": " << totalArticulosFiltrados << std::endl;
                }
            }},


/*    {"stock", [&mapaArticulos](const std::string& param) {
      auto params = splitCSVLine(param);
        std::string codigoBarras = params[0];
      if (params.size() == 1) {
        int stockTotal = getStockTotal(mapaArticulos, codigoBarras);
        std::cout << "Stock total del articulo '" << codigoBarras << "': " << stockTotal << std::endl;
      }
      else {
        int deposito = std::stoi(params[1]);
        int stockTotal = getStockTotal(mapaArticulos, codigoBarras, deposito);
        std::cout << "Stock del articulo '" << codigoBarras << "' en el deposito #" << deposito << ": " << stockTotal << std::endl;
      }
    }},*/

            {"stock",         [&mapaArticulos](const std::string &param) {
                auto params = splitCSVLine(param);
                if (params.size() == 1) {
                    std::string codigoBarras = params[0];
                    if (mapaArticulos.find(codigoBarras) == mapaArticulos.end()) {
                        std::cerr << "Error: El código de barras no existe en el mapa de artículos." << std::endl;
                        return;
                    }
                    int stockTotal = getStockTotal(mapaArticulos, codigoBarras);
                    std::cout << "Stock total del artículo '" << codigoBarras << "': " << stockTotal << std::endl;
                } else if (params.size() == 2) {
                    std::string codigoBarras = params[0];
                    int deposito;
                    try {
                        deposito = std::stoi(params[1]);
                    } catch (const std::invalid_argument &) {
                        std::cerr << "Error: El valor del depósito no es un número válido." << std::endl;
                        return;
                    }
                    if (deposito <= 0) {
                        std::cerr << "Error: El valor del depósito debe ser mayor que cero." << std::endl;
                        return;
                    }
                    if (mapaArticulos.find(codigoBarras) == mapaArticulos.end()) {
                        std::cerr << "Error: El código de barras no existe en el mapa de artículos." << std::endl;
                        return;
                    }
                    int stockTotal = getStockTotal(mapaArticulos, codigoBarras, deposito);
                    std::cout << "Stock del artículo '" << codigoBarras << "' en el depósito #" << deposito << ": "
                              << stockTotal << std::endl;
                } else {
                    std::cerr << "Error: Formato incorrecto para stock." << std::endl;
                }
            }},



            /* {"max_stock", [&depositos](const std::string& param) {
               auto params = splitCSVLine(param);
               if (params.size() == 1) {
                 int minStock = std::stoi(params[0]);
                 int totalArticulosFiltrados = mostrarArticulosConStockMayorOIgualA(depositos[0], minStock);
                 std::cout << "Cantidad de articulos totales con stock menor o igual a " << minStock << ": " << totalArticulosFiltrados << std::endl;
               }
             }}
           };*/

            {"max_stock",     [&depositos](const std::string &param) {
                auto params = splitCSVLine(param);
                if (params.size() == 1) {
                    int maxStock;
                    try {
                        maxStock = std::stoi(params[0]);
                    } catch (const std::invalid_argument &) {
                        std::cerr << "Error: El valor n no es un número válido." << std::endl;
                        return;
                    }
                    if (maxStock < 0) {
                        std::cerr << "Error: El valor n debe ser mayor que cero." << std::endl;
                        return;
                    }
                    int totalArticulosFiltrados = mostrarArticulosConStockMayorOIgualA(depositos[0], maxStock);
                    std::cout << "Cantidad de artículos totales con stock mayor o igual a " << maxStock << ": "
                              << totalArticulosFiltrados << std::endl;
                } else {
                    std::cerr << "Error: Formato incorrecto." << std::endl;
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