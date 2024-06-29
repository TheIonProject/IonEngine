# Root project cmake

# Cmake min version
cmake_minimum_required(VERSION 3.25 FATAL_ERROR)

# C++ version
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)


project(IonEngine)

add_subdirectory(ion)
