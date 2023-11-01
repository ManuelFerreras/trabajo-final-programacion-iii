#ifndef TRABAJO_FINAL_PROGRAMACION_III_ARTICLESMAP_H
#define TRABAJO_FINAL_PROGRAMACION_III_ARTICLESMAP_H

#include "ArticlesMap.h"
#include <iostream>
#include <unordered_map>
#include "../../constants/Structs.h"

/*
 * Conseguimos el total de articulos diferentes a partir del tamaño del mapa.
 */
int getTotalArticulosDiferentes(const std::unordered_map<std::string, Articulo>& mapaArticulos);

/*
 * Conseguimos el total de articulos a partir de la suma de todos los stocks de cada articulo.
 */
int getTotalArticulos(const std::unordered_map<std::string, Articulo>& mapaArticulos);

/*
 * Conseguimos el stock total de un articulo a partir de su codigo de barras.
 */
int getStockTotal(const std::unordered_map<std::string, Articulo>& mapaArticulos, const std::string& codigoBarras);

/*
 * Conseguimos el stock total de un articulo a partir de su codigo de barras y el deposito.
 */
int getStockTotal(const std::unordered_map<std::string, Articulo>& mapaArticulos, const std::string& codigoBarras, int deposito);

#endif //TRABAJO_FINAL_PROGRAMACION_III_ARTICLESMAP_H
