cmake_minimum_required(VERSION 3.28)
include(FetchContent)

project(LeadTheHordes)

option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

# configs
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_CONFIGURATION_TYPES Debug;Release CACHE STRING build_configurations)

# set variables


if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(ARCHITECTURE x64)
else()
    set(ARCHITECTURE x86)
endif()



# set(OUTPUT_DIR_NAME                         ${CMAKE_SYSTEM_NAME}_${CMAKE_CXX_COMPILER_ID})

# # set output behaviors
# set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY          ${CMAKE_SOURCE_DIR}/lib/${OUTPUT_DIR_NAME}-${ARCHITECTURE})
# set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE  ${CMAKE_SOURCE_DIR}/lib/${OUTPUT_DIR_NAME}_RELEASE-${ARCHITECTURE})
# set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG    ${CMAKE_SOURCE_DIR}/lib/${OUTPUT_DIR_NAME}_DEBUG-${ARCHITECTURE})

# set(CMAKE_LIBRARY_OUTPUT_DIRECTORY          ${CMAKE_SOURCE_DIR}/lib/${OUTPUT_DIR_NAME}-${ARCHITECTURE})
# set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE  ${CMAKE_SOURCE_DIR}/lib/${OUTPUT_DIR_NAME}_RELEASE-${ARCHITECTURE})
# set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG    ${CMAKE_SOURCE_DIR}/lib/${OUTPUT_DIR_NAME}_DEBUG-${ARCHITECTURE})

# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY          ${CMAKE_SOURCE_DIR}/bin/${OUTPUT_DIR_NAME}-${ARCHITECTURE})
# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE  ${CMAKE_SOURCE_DIR}/bin/${OUTPUT_DIR_NAME}_RELEASE-${ARCHITECTURE})
# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG    ${CMAKE_SOURCE_DIR}/bin/${OUTPUT_DIR_NAME}_DEBUG-${ARCHITECTURE})


set(OUTPUT_DIR_NAME                         ${CMAKE_SYSTEM_NAME}_${CMAKE_CXX_COMPILER_ID}-${ARCHITECTURE})

# set output behaviors
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY          ${CMAKE_SOURCE_DIR}/lib/${OUTPUT_DIR_NAME})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE  ${CMAKE_SOURCE_DIR}/lib/${OUTPUT_DIR_NAME})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG    ${CMAKE_SOURCE_DIR}/lib/${OUTPUT_DIR_NAME})

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY          ${CMAKE_SOURCE_DIR}/lib/${OUTPUT_DIR_NAME})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE  ${CMAKE_SOURCE_DIR}/lib/${OUTPUT_DIR_NAME})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG    ${CMAKE_SOURCE_DIR}/lib/${OUTPUT_DIR_NAME})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY          ${CMAKE_SOURCE_DIR}/bin/${OUTPUT_DIR_NAME})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE  ${CMAKE_SOURCE_DIR}/bin/${OUTPUT_DIR_NAME})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG    ${CMAKE_SOURCE_DIR}/bin/${OUTPUT_DIR_NAME})



# set to use static library runtime
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

# needs testing for gcc and clang
# if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
#     target_link_options(MyTarget PRIVATE
#         $<$<CONFIG:Debug>:-static-libgcc -static-libstdc++>
#         $<$<CONFIG:Release>:-static-libgcc -static-libstdc++>
#     )
# endif()

# dependencies
add_compile_definitions(SFML_STATIC)

FetchContent_Declare(sfml
    GIT_REPOSITORY  https://github.com/SFML/SFML.git
    GIT_TAG         2.6.x
    GIT_SHALLOW     ON
    EXCLUDE_FROM_ALL
    SYSTEM
)
FetchContent_MakeAvailable(sfml)

add_subdirectory(Eris_Log)


add_executable(LeadTheHordes)
target_compile_features(LeadTheHordes PRIVATE cxx_std_17)


set_property(TARGET LeadTheHordes 
    PROPERTY VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
)

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT LeadTheHordes)




if(WIN32)
    add_custom_command(
        TARGET LeadTheHordes
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/${ARCHITECTURE}/openal32.dll $<TARGET_FILE_DIR:LeadTheHordes>
        COMMENT Copying OpenAL dll to output directory
        VERBATIM
    )
endif()

add_custom_command(
    TARGET LeadTheHordes POST_BUILD 
    COMMAND ${CMAKE_COMMAND} -E copy 
    ${CMAKE_SOURCE_DIR}/LeadTheHordes/config
    $<TARGET_FILE_DIR:LeadTheHordes>
    COMMENT Copying config files to output directory
)


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
    # ${CMAKE_SOURCE_DIR}/lib/${OUTPUT_DIR_NAME}
    sfml-SOURCE_DIR
)

# Link dependencies
target_link_libraries(LeadTheHordes PRIVATE
    Eris_Log
    sfml-graphics
    sfml-audio
    
    # sfml-graphics-s$<$<CONFIG:Debug>:-d>
    # sfml-audio-s$<$<CONFIG:Debug>:-d>
    # sfml-window-s$<$<CONFIG:Debug>:-d>
    # sfml-system-s$<$<CONFIG:Debug>:-d>
    
)
