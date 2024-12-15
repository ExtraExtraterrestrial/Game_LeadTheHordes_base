cmake_minimum_required(VERSION 3.28)
include(FetchContent)

### PACKAGES TO PREINSTALL ON LINUX ###
# libxrandr-dev \
#     libxcursor-dev \
#     libudev-dev \
#     libfreetype-dev \
#     libopenal-dev \
#     libflac-dev \
#     libvorbis-dev \
#     libgl1-mesa-dev \
#     libegl1-mesa-dev

project(LeadTheHordes)

# configs
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(SFML_VERSION "2.6.x")

option(BUILD_SHARED_LIBS "Build shared libraries" OFF)
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

add_executable(LeadTheHordes)

add_compile_definitions(SFML_STATIC)
target_compile_options(LeadTheHordes PRIVATE -Wall)


# if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
#     target_link_options(MyTarget PRIVATE
#         $<$<CONFIG:Debug>:-static-libgcc -static-libstdc++>
#         $<$<CONFIG:Release>:-static-libgcc -static-libstdc++>
#     )
# endif()

set(CMAKE_CONFIGURATION_TYPES Debug;Release CACHE STRING build_configurations)

set(OUTPUT_DIR_NAME ${CMAKE_SYSTEM_NAME}_${CMAKE_GENERATOR}_${CMAKE_BUILD_TYPE}-${CMAKE_SYSTEM_PROCESSOR})
set(PROJECT_BINARY_DIR ${CMAKE_CURRENT_LIST_DIR}/bin/${OUTPUT_DIR_NAME})
# set(OBJECT_DIR ${CMAKE_CURRENT_LIST_DIR}/obj/${OUTPUT_DIR_NAME})

# SOURCES - all the source files of LeadTheHordes
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
    ${CMAKE_SOURCE_DIR}/LeadTheHordes/src/*.cpp
    ${CMAKE_SOURCE_DIR}/LeadTheHordes/src/*.tpp
    ${CMAKE_SOURCE_DIR}/LeadTheHordes/src/*.hpp
    ${CMAKE_SOURCE_DIR}/LeadTheHordes/src/*.h
)


FetchContent_Declare(sfml
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM
    SOURCE_DIR ${CMAKE_SOURCE_DIR}/SFML
    PREFIX ${CMAKE_SOURCE_DIR}/SFML
)

FetchContent_MakeAvailable(sfml)


if(NOT sfml_POPULATED)
    FetchContent_Populate(sfml)
    add_subdirectory(${sfml_SOURCE_DIR} ${sfml_BINARY_DIR})
endif()

# Include dependencies
add_subdirectory(Eris_Log)

file(COPY ${CMAKE_SOURCE_DIR}/LeadTheHordes/config DESTINATION ${PROJECT_BINARY_DIR})
    

# set definition HORDES_DEBUG or HORDES_RELEASE
target_compile_definitions (LeadTheHordes
    PRIVATE HORDES_$<$<CONFIG:Debug>:DEBUG>$<$<CONFIG:Release>:RELEASE>
)

# set_target_properties(LeadTheHordes PROPERTIES
#     RUNTIME_OUTPUT_DIRECTORY ${BINARY_DIR}
# )

# Target source files
target_sources(LeadTheHordes PRIVATE ${SOURCES})

# Precompiled headers
target_precompile_headers(LeadTheHordes PRIVATE ${CMAKE_SOURCE_DIR}/LeadTheHordes/src/Hordes_pch.h)

# Include directories
target_include_directories(LeadTheHordes PRIVATE
    ${CMAKE_SOURCE_DIR}/LeadTheHordes/src
    ${CMAKE_SOURCE_DIR}/Eris_Log/include
    ${CMAKE_SOURCE_DIR}/SFML/include
)

# Libraries
target_link_directories(LeadTheHordes PRIVATE
    ${CMAKE_SOURCE_DIR}/Eris_Log/lib/${OUTPUT_DIR_NAME}
    ${CMAKE_SOURCE_DIR}/SFML/lib
)

# Link dependencies
target_link_libraries(LeadTheHordes PRIVATE
    Eris_Log
    
    sfml-graphics-s$<$<CONFIG:Debug>:-d>
    sfml-audio-s$<$<CONFIG:Debug>:-d>
    sfml-window-s$<$<CONFIG:Debug>:-d>
    sfml-system-s$<$<CONFIG:Debug>:-d>
    
    flac
    vorbisenc
    vorbisfile
    vorbis
    ogg
    openal32
    winmm
    opengl32
    freetype
    gdi32
)
