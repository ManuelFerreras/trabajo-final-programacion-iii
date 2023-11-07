#include <iostream>
#include <functional>
#include <unordered_map>
#include <map>
#include "utils/csv/CSVReader.h"
#include "utils/deposit/DepositTree.h"
#include "utils/map/ArticlesMap.h"
#include "utils/validations/validaciones.h"


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