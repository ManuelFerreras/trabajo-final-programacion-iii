#ifndef TRABAJO_FINAL_PROGRAMACION_III_DEPOSITTREE_H
#define TRABAJO_FINAL_PROGRAMACION_III_DEPOSITTREE_H

#include "DepositTree.h"
#include <iostream>
#include <map>

/*
 * Función que muestra los artículos con stock menor o igual a 'stockMax'.
 * */
int mostrarArticulosConStockMenorOIgualA(const std::multimap<int, std::string>& deposito, int stockMax);

#endif //TRABAJO_FINAL_PROGRAMACION_III_DEPOSITTREE_H
