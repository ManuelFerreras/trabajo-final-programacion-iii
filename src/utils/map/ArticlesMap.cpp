#include "ArticlesMap.h"
#include <iostream>
#include "../../constants/Structs.h"

int getTotalArticulosDiferentes(const std::unordered_map<std::string, Articulo>& mapaArticulos) {
  return mapaArticulos.size();
}

int getStockTotal(const std::unordered_map<std::string, Articulo>& mapaArticulos, const std::string& codigoBarras) {
  auto it = mapaArticulos.find(codigoBarras);
  if (it == mapaArticulos.end()) {
    return 0;
  }
  return it->second.stockTotal;
}

int getStockTotal(const std::unordered_map<std::string, Articulo>& mapaArticulos, const std::string& codigoBarras, int deposito) {
  auto it = mapaArticulos.find(codigoBarras);
  if (it == mapaArticulos.end()) {
    return 0;
  }
  return it->second.stockPorDeposito[deposito];
}
