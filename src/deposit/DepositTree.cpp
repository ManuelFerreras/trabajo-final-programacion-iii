#include "DepositTree.h"
#include <iostream>
#include <map>

int mostrarArticulosConStockMenorOIgualA(const std::multimap<int, std::string>& deposito, int stockMax) {
  auto it = deposito.lower_bound(stockMax + 1); // Encuentra el primer elemento que no cumple con la condición
  int cantidadArticulos = std::distance(deposito.begin(), it);

  for (auto begin = deposito.begin(); begin != it; ++begin) {
    std::cout << "Stock: " << begin->first << ", Codigo de Barras: " << begin->second << "\n";
  }

  return cantidadArticulos;
}