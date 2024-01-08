cmake_minimum_required(VERSION 3.27)
project(vega)

set(CMAKE_CXX_STANDARD 23)

find_package(Boost REQUIRED json system)

include_directories(.)
include_directories(shared)


add_library(vega_utils
        shared/Vega.hpp
        shared/CommandTemplate.cpp
        shared/CommandTemplate.hpp
        shared/VegaModule.hpp)
target_link_libraries(vega_utils Boost::json)
