cmake_minimum_required(VERSION 3.15)
project(Multiphase_sorting)

set(CMAKE_CXX_STANDARD 14)
set(DCMAKE_SH="CMAKE_SH-NOTFOUND")

add_executable(Multiphase_sorting main.cpp files.cpp files.h sort.cpp sort.h)