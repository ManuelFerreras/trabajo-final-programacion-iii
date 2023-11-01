#include <iostream>
#include <unordered_map>
#include <map>
#include "utils/csv/CSVReader.h"
#include "utils/deposit/DepositTree.h"
#include "utils/map/ArticlesMap.h"

std::unordered_map<std::string, std::function<void(const std::string&)>> routerDeArgumentos(
    std::unordered_map<std::string, Articulo>& mapaArticulos,
    std::vector<std::multimap<int, std::string>>& depositos
) {
  // Definimos las acciones como funciones lambda.
  std::unordered_map<std::string, std::function<void(const std::string&)>> acciones = {
    {"total_art_dif", [&mapaArticulos](const std::string& param) {
      int cantidadArticulos = getTotalArticulosDiferentes(mapaArticulos);
      std::cout << "Cantidad de articulos diferentes: " << cantidadArticulos << std::endl;
      return;
    }},

    {"total_art", [&mapaArticulos](const std::string& param) {
      int cantidadArticulos = getTotalArticulos(mapaArticulos);
      std::cout << "Cantidad de articulos: " << cantidadArticulos << std::endl;
      return;
    }},

    {"min_stock", [&depositos](const std::string& param) {
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
    }},

    {"stock", [&mapaArticulos](const std::string& param) {
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
    }},

    {"max_stock", [&depositos](const std::string& param) {
      auto params = splitCSVLine(param);
      if (params.size() == 1) {
        int minStock = std::stoi(params[0]);
        int totalArticulosFiltrados = mostrarArticulosConStockMayorOIgualA(depositos[0], minStock);
        std::cout << "Cantidad de articulos totales con stock menor o igual a " << minStock << ": " << totalArticulosFiltrados << std::endl;
      }
    }}
  };

  return acciones;
}

int main(int argc, char* argv[]) {
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
  std::unordered_map<std::string, Articulo> mapaArticulos = leerCSV(archivoCSV, depositos);

  /*
   * Procesamos el argumento ingresado.
   */
  std::unordered_map<std::string, std::function<void(const std::string&)>> acciones = routerDeArgumentos(mapaArticulos, depositos);

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