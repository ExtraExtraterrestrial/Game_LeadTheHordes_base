cmake_minimum_required(VERSION 3.28)
include(FetchContent)

project(LeadTheHordes)

option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

# configs
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

# if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
#     target_link_options(MyTarget PRIVATE
#         $<$<CONFIG:Debug>:-static-libgcc -static-libstdc++>
#         $<$<CONFIG:Release>:-static-libgcc -static-libstdc++>
#     )
# endif()

if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(ARCHITECTURE x64)
else()
    set(ARCHITECTURE x86)
endif()


set(OUTPUT_DIR_NAME ${CMAKE_SYSTEM_NAME}_${CMAKE_CXX_COMPILER_ID}-${ARCHITECTURE})

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib/${OUTPUT_DIR_NAME})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/lib/${OUTPUT_DIR_NAME})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/${OUTPUT_DIR_NAME})

add_compile_definitions(SFML_STATIC)

add_subdirectory(Eris_Log)

FetchContent_Declare(sfml
    GIT_REPOSITORY  https://github.com/SFML/SFML.git
    GIT_TAG         2.6.x
    GIT_SHALLOW     ON
    EXCLUDE_FROM_ALL
    SYSTEM
)
FetchContent_MakeAvailable(sfml)


add_executable(LeadTheHordes)
target_compile_features(LeadTheHordes PRIVATE cxx_std_17)
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT LeadTheHordes)

target_link_libraries(LeadTheHordes PRIVATE 
    sfml-graphics
    sfml-audio
)

if(WIN32)
    add_custom_command(
        TARGET LeadTheHordes
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/${ARCHITECTURE}/openal32.dll $<TARGET_FILE_DIR:LeadTheHordes>
        VERBATIM
    )
endif()

# check if this copies on build or on cmake build omg I hate cmake so much
file(COPY ${CMAKE_SOURCE_DIR}/LeadTheHordes/config DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

set(CMAKE_CONFIGURATION_TYPES Debug;Release CACHE STRING build_configurations)


# check_type_size("void*" SIZEOF_VOID_P BUILTIN_TYPES_ONLY)

# SOURCES - all the source files of LeadTheHordes
file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
    ${CMAKE_SOURCE_DIR}/LeadTheHordes/src/*.cpp
    ${CMAKE_SOURCE_DIR}/LeadTheHordes/src/*.tpp
    ${CMAKE_SOURCE_DIR}/LeadTheHordes/src/*.hpp
    ${CMAKE_SOURCE_DIR}/LeadTheHordes/src/*.h
)


# set definition HORDES_DEBUG or HORDES_RELEASE
target_compile_definitions (LeadTheHordes
    PRIVATE HORDES_$<$<CONFIG:Debug>:DEBUG>$<$<CONFIG:Release>:RELEASE>
)

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
    # ${CMAKE_SOURCE_DIR}/SFML/lib
    sfml-SOURCE_DIR
)

# Link dependencies
target_link_libraries(LeadTheHordes PRIVATE
    Eris_Log
    
    # sfml-graphics-s$<$<CONFIG:Debug>:-d>
    # sfml-audio-s$<$<CONFIG:Debug>:-d>
    # sfml-window-s$<$<CONFIG:Debug>:-d>
    # sfml-system-s$<$<CONFIG:Debug>:-d>
    
    # flac
    # vorbisenc
    # vorbisfile
    # vorbis
    # ogg
    # openal32
    # winmm
    # opengl32
    # freetype
    # gdi32
)
