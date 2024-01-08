cmake_minimum_required(VERSION 3.27)
project(vega)

set(CMAKE_CXX_STANDARD 23)



include_directories(.)
include_directories(shared)

add_library(vega
        shared/Vega.hpp)
