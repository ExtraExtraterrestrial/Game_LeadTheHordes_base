cmake_minimum_required(VERSION 3.28)

project(Eris_Log LANGUAGES CXX)

# configs
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


# Target source files
# target_sources(Eris_Log PRIVATE
add_library(Eris_Log STATIC
    ${CMAKE_CURRENT_LIST_DIR}/include/Eris_Log/TimeFormatter.h
    ${CMAKE_CURRENT_LIST_DIR}/include/Eris_Log/Log.h
    ${CMAKE_CURRENT_LIST_DIR}/src/TimeFormatter.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/Log.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/Log.tpp
)


# set definitions
target_compile_definitions (Eris_Log
    PRIVATE LOG_DO_NOT_AUTOSTART
)

# Include directories
target_include_directories(Eris_Log PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/src
    ${CMAKE_CURRENT_LIST_DIR}/include
)