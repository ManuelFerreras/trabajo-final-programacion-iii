cmake_minimum_required(VERSION 3.26)
project(trabajo_final_programacion_iii)

set(CMAKE_CXX_STANDARD 14)

add_executable(trabajo_final_programacion_iii
        src/utils/map/ArticlesMap.h
        src/utils/map/ArticlesMap.cpp
        src/utils/deposit/DepositTree.h
        src/utils/deposit/DepositTree.cpp
        src/utils/csv/CSVReader.h
        src/utils/csv/CSVReader.cpp
        src/main.cpp
        src/utils/validations/validaciones.h
        src/utils/validations/validaciones.cpp
)
