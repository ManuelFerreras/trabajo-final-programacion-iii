cmake_minimum_required(VERSION 3.26)
project(trabajo_final_programacion_iii)

set(CMAKE_CXX_STANDARD 14)

include_directories(src/utils)

add_executable(trabajo_final_programacion_iii
        src/utils/Utils.h
        src/utils/Utils.cpp
        src/map/ArticlesMap.h
        src/map/ArticlesMap.cpp
        src/deposit/DepositTree.h
        src/deposit/DepositTree.cpp
        src/csv/CSVReader.h
        src/csv/CSVReader.cpp
        src/main.cpp)
