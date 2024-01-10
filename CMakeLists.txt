cmake_minimum_required(VERSION 3.27)
project(vega)

set(CMAKE_CXX_STANDARD 23)

add_compile_options(-fPIC)

# preprocessor definitions
add_compile_definitions(DEBUG=$<CONFIG:Debug>
        PROJECT_DIR="${CMAKE_SOURCE_DIR}"
        BINARY_DIR="${CMAKE_BINARY_DIR}"
)

find_package(Boost COMPONENTS json system filesystem REQUIRED)

include_directories(.)
include_directories(shared)

# targets
add_library(vega_utils
        shared/Vega.hpp
        shared/CommandTemplate.cpp
        shared/CommandTemplate.hpp
        shared/VegaModule.hpp
        shared/SettingLoader.cpp
        shared/SettingLoader.hpp
        shared/Log.cpp
        shared/Log.hpp
)
target_link_libraries(vega_utils
        Boost::json
        Boost::filesystem
)

add_library(core SHARED
        core/CoreModule.cpp
        core/CoreModule.hpp)

add_executable(server server/main.cpp
        server/ServerBuilder.cpp
        server/ServerBuilder.hpp
        server/Application.cpp
        server/Application.hpp
)
target_link_libraries(server
        vega_utils
        ${Boost_LIBRARIES}
)
