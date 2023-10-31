#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <unordered_map>

struct Articulo {
    std::string grupo;
    std::string nombre;
    std::vector<int> stockPorDeposito; // Almacena el stock de cada depósito
    int stockTotal = 0; // Sumatoria del stock en todos los depósitos
};

std::vector<std::string> splitCSVLine(const std::string& linea) {
  std::vector<std::string> campos;
  std::string campo;
  bool dentroDeComillas = false;

  for (char c : linea) {
    if (c == '"') {
      dentroDeComillas = !dentroDeComillas;
    } else if (c == ',' && !dentroDeComillas) {
      campos.push_back(campo);
      campo.clear();
    } else {
      campo += c;
    }
  }
  campos.push_back(campo);
  return campos;
}

std::unordered_map<std::string, Articulo> leerCSV(const std::string& archivo) {
  std::ifstream file(archivo);
  if (!file.is_open()) {
    std::cerr << "No se pudo abrir el archivo " << archivo << std::endl;
    return {};
  }

  std::string linea;
  std::getline(file, linea); // Leer la primera línea (encabezados)

  std::vector<std::string> encabezados = splitCSVLine(linea);
  int numDepositos = encabezados.size() - 3; // Restamos las primeras 3 columnas fijas

  std::unordered_map<std::string, Articulo> articulos;

  // Leer y procesar cada línea
  while (std::getline(file, linea)) {
    std::vector<std::string> campos = splitCSVLine(linea);
    Articulo articulo;

    articulo.grupo = campos[0];
    std::string codigoBarras = campos[1];
    articulo.nombre = campos[2];

    for (int i = 3; i < 3 + numDepositos; ++i) {
      std::string stockStr = campos[i];
      int stock = 0;
      if (!stockStr.empty()) {
        try {
          stock = std::stoi(stockStr);
        } catch (const std::invalid_argument& e) {
          std::cerr << "Error al convertir a entero: " << stockStr << std::endl;
        }
      }
      articulo.stockPorDeposito.push_back(stock);
      articulo.stockTotal += stock;
    }

    articulos[codigoBarras] = articulo;
  }

  file.close();
  return articulos;
}

int main() {
  auto mapaArticulos = leerCSV("../data/inventarioFisico.csv");
  // Procesa el mapa de artículos como lo necesites

  // Por ejemplo, imprimir los nombres de los artículos y su stock total:
  for (const auto& par : mapaArticulos) {
    std::cout << par.second.nombre << ": " << par.second.stockTotal << std::endl;
  }

  // Imprimir un articulo especifico.
  std::cout << "Articulo: " << mapaArticulos["RD-REJOIMP 150"].nombre << ": " << mapaArticulos["RD-REJOIMP 150"].stockTotal << std::endl;

  return 0;
}