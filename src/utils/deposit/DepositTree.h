#ifndef TRABAJO_FINAL_PROGRAMACION_III_DEPOSITTREE_H
#define TRABAJO_FINAL_PROGRAMACION_III_DEPOSITTREE_H

#include "DepositTree.h"
#include <iostream>
#include <map>

/*
 * Función que muestra los artículos con stock menor o igual a 'stockMax'.
 * */
int mostrarArticulosConStockMenorOIgualA(const std::multimap<int, std::string>& deposito, int stockMax);

/*
 * Función que muestra los artículos con stock mayor o igual a 'stockMin'.
 * */
int mostrarArticulosConStockMayorOIgualA(const std::multimap<int, std::string>& deposito, int stockMin);

#endif //TRABAJO_FINAL_PROGRAMACION_III_DEPOSITTREE_H
