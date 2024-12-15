cmake_minimum_required(VERSION 3.16)

project(Eris_Log LANGUAGES CXX)

# configs
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

set(CMAKE_CONFIGURATION_TYPES Debug;Release CACHE STRING build_configurations)  

set(OUTPUT_DIR_NAME ${CMAKE_SYSTEM_NAME}_${CMAKE_GENERATOR}_${CMAKE_BUILD_TYPE}-${CMAKE_SYSTEM_PROCESSOR})
set(PROJECT_BINARY_DIR ${CMAKE_CURRENT_LIST_DIR}/lib/${OUTPUT_DIR_NAME})

# Target source files
# target_sources(Eris_Log PRIVATE
add_library(Eris_Log STATIC
    ${CMAKE_CURRENT_LIST_DIR}/include/Eris_Log/TimeFormatter.h
    ${CMAKE_CURRENT_LIST_DIR}/include/Eris_Log/Log.h
    ${CMAKE_CURRENT_LIST_DIR}/src/TimeFormatter.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/Log.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/Log.tpp
)


# set definition HORDES_DEBUG or HORDES_RELEASE
target_compile_definitions (Eris_Log
    PRIVATE LOG_DO_NOT_AUTOSTART
)

set_target_properties(Eris_Log PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}
)

# Include directories
target_include_directories(Eris_Log PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/src
    ${CMAKE_CURRENT_LIST_DIR}/include
)