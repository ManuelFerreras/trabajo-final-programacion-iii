# Trabajo Final de Programación III

## Integrantes:
- _Franco Casavecchia_
- _Victoria Sponton_
- _Manuel Ferreras_
- _Martina Becerra_

## Ejercitacion:
Link a la [Ejercitacion](https://presencial.ucc.edu.ar/pluginfile.php/1193586/mod_resource/content/0/prog%203%20parcial%202.pdf)
 
## Diagrama de Clases:

## Instrucciones de Uso:

1) Primero, tendremos que crear un build del proyecto para poder ejecutarlo en el OS que querramos. 
<br></br>

2) Abrimos una terminal en el archivo generado (llamado `cmake-build-debug` por CLion).
<br></br>

3) Podemos ejecutar el programa con el siguiente comando:
```bash
./trabajo_final_programacion_iii "argumento" "path al csv"
```
<br></br>

### Ejemplos de Comandos:
- Ejecutar la función `total_art_dif`:
```bash
./trabajo_final_programacion_iii total_art_dif ../data/inventarioFisico.csv
```
<br>

- Ejecutar la función `total_art`:
```bash
./trabajo_final_programacion_iii total_art_dif ../data/inventarioFisico.csv
```
<br>

- Ejecutar la función `min_stock` sin deposito específico, dado un `n` -> Stock Mínimo:
```bash
./trabajo_final_programacion_iii "min_stock[n]" ../data/inventarioFisico.csv
```
<br>

- Ejecutar la función `min_stock` con deposito específico, dado un `n` -> Stock Mínimo, y un `m` -> Número de Depósito:
```bash
./trabajo_final_programacion_iii "min_stock[n,m]" ../data/inventarioFisico.csv
```
<br>

- Ejecutar la función `stock` sin deposito específico, dado un `n` -> Código de Barras:
```bash
./trabajo_final_programacion_iii "stock[\"n\"]" ../data/inventarioFisico.csv
```
<br>

- Ejecutar la función `stock` con deposito específico, dado un `n` -> Código de Barras, y un `m` -> Número de Depósito:
```bash
./trabajo_final_programacion_iii "stock[\"n\",m]" ../data/inventarioFisico.csv
```
<br>

- Ejecutar la función `max_stock` sin deposito específico, dado un `n` -> Stock Máximo:
```bash
./trabajo_final_programacion_iii "max_stock[n]" ../data/inventarioFisico.csv
```
<br>

### Uso Normal
- Procesador_inventario.exe [Argumentos] inventarioFisico.csv

### Argumentos:
```console
- total_art_dif                       : Cantidad de articulos diferentes.
- total_art                           : Cantidad de articulos totales.
- min_stock[n]                        : Listado de articulos con n o menos unidades en stock.
- min_stock[n],[deposito]             : Listado de articulos con n o menos unidades en stock segun el deposito.
- stock[codigo_de_barra]              : Stock total del articulo
- stock[codigo_de_barra],[deposito]   : Stock total del articulo segun el deposito
- max_stock[n]                        : Listado de articulos con n o mas unidades en stock.
```

## Overview del Proyecto:
