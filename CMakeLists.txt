cmake_minimum_required(VERSION 3.16)

project(LeadTheHordes)

# configs
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


### PACKAGES TO PREINSTALL ###
# freetype
# x11
# xrandr
# udev
# opengl
# flac
# ogg
# vorbis
# vorbisenc
# vorbisfile
# openal
# pthread



# set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

# #!# Clang untested
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


# Define SFML_DIR based on platform
if(WIN32)
    if(CMAKE_GENERATOR MATCHES "Visual Studio 16")
        set(SFML_DIR ${CMAKE_CURRENT_LIST_DIR}/SFML/Windows_vs19)
    elseif(CMAKE_GENERATOR MATCHES "Visual Studio 17")
        set(SFML_DIR ${CMAKE_CURRENT_LIST_DIR}/SFML/Windows_vs22)
    elseif(CMAKE_GENERATOR MATCHES "MinGW" OR CMAKE_GENERATOR MATCHES "Clang")
        set(SFML_DIR ${CMAKE_CURRENT_LIST_DIR}/SFML/Windows_GCC)
    endif()
elseif(UNIX AND NOT APPLE)
    set(SFML_DIR ${CMAKE_CURRENT_LIST_DIR}/SFML/Linux_GCC)
else()
    message(FATAL_ERROR "Mac not supported yet!")
endif()


# SOURCES - all the source files of LeadTheHordes
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
    ${CMAKE_CURRENT_LIST_DIR}/LeadTheHordes/src/*.cpp
    ${CMAKE_CURRENT_LIST_DIR}/LeadTheHordes/src/*.tpp
    ${CMAKE_CURRENT_LIST_DIR}/LeadTheHordes/src/*.hpp
    ${CMAKE_CURRENT_LIST_DIR}/LeadTheHordes/src/*.h
)


# Include dependencies
add_subdirectory(Eris_Log)
# add_subdirectory(SFML)

file(COPY ${CMAKE_CURRENT_LIST_DIR}/LeadTheHordes/config DESTINATION ${PROJECT_BINARY_DIR})
    
add_executable(LeadTheHordes)

add_compile_definitions(SFML_STATIC)

# set definition HORDES_DEBUG or HORDES_RELEASE
target_compile_definitions (LeadTheHordes
    PRIVATE HORDES_$<$<CONFIG:Debug>:DEBUG>$<$<CONFIG:Release>:RELEASE>
)

# set_target_properties(LeadTheHordes PROPERTIES
#     RUNTIME_OUTPUT_DIRECTORY ${BINARY_DIR}
# )

# Target source files
target_sources(LeadTheHordes PRIVATE
    ${SOURCES}
)

# Precompiled headers
target_precompile_headers(LeadTheHordes PRIVATE ${CMAKE_CURRENT_LIST_DIR}/LeadTheHordes/src/Hordes_pch.h)

# Include directories
target_include_directories(LeadTheHordes PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/LeadTheHordes/src
    ${CMAKE_CURRENT_LIST_DIR}/Eris_Log/include
    # ${CMAKE_CURRENT_LIST_DIR}/SFML/include
    ${SFML_DIR}/include
)

# Libraries
target_link_directories(LeadTheHordes PRIVATE
    ${CMAKE_CURRENT_LIST_DIR}/Eris_Log/lib/${OUTPUT_DIR_NAME}
    # ${CMAKE_CURRENT_LIST_DIR}/SFML/lib
    ${SFML_DIR}/lib
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

