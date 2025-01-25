cmake_minimum_required(VERSION 3.28)
include(FetchContent)

project(LeadTheHordes)

### CONFIGS ###
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


# set to use static library runtime
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
add_compile_definitions(SFML_STATIC)

# needs testing for gcc and clang
# if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
#     target_link_options(MyTarget PRIVATE
#         $<$<CONFIG:Debug>:-static-libgcc -static-libstdc++>
#         $<$<CONFIG:Release>:-static-libgcc -static-libstdc++>
#     )
# endif()


### VARIABLES ###
if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(ARCHITECTURE x64)
else()
    set(ARCHITECTURE x86)
endif()

# set output behaviors
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY          ${CMAKE_SOURCE_DIR}/bin/${CMAKE_SYSTEM_NAME}_${CMAKE_CXX_COMPILER_ID}-${ARCHITECTURE})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG    ${CMAKE_SOURCE_DIR}/bin/${CMAKE_SYSTEM_NAME}_${CMAKE_CXX_COMPILER_ID}_DEBUG-${ARCHITECTURE})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE  ${CMAKE_SOURCE_DIR}/bin/${CMAKE_SYSTEM_NAME}_${CMAKE_CXX_COMPILER_ID}_RELEASE-${ARCHITECTURE})

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY          ${CMAKE_SOURCE_DIR}/lib/${CMAKE_SYSTEM_NAME}_${CMAKE_CXX_COMPILER_ID}-${ARCHITECTURE})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_DEBUG    ${CMAKE_SOURCE_DIR}/lib/${CMAKE_SYSTEM_NAME}_${CMAKE_CXX_COMPILER_ID}_DEBUG-${ARCHITECTURE})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_RELEASE  ${CMAKE_SOURCE_DIR}/lib/${CMAKE_SYSTEM_NAME}_${CMAKE_CXX_COMPILER_ID}_RELEASE-${ARCHITECTURE})

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY          ${CMAKE_SOURCE_DIR}/lib/${CMAKE_SYSTEM_NAME}_${CMAKE_CXX_COMPILER_ID}-${ARCHITECTURE})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_DEBUG    ${CMAKE_SOURCE_DIR}/lib/${CMAKE_SYSTEM_NAME}_${CMAKE_CXX_COMPILER_ID}_DEBUG-${ARCHITECTURE})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY_RELEASE  ${CMAKE_SOURCE_DIR}/lib/${CMAKE_SYSTEM_NAME}_${CMAKE_CXX_COMPILER_ID}_RELEASE-${ARCHITECTURE})


### DEPENDENCIES ###
FetchContent_Declare(SFML
    GIT_REPOSITORY  https://github.com/SFML/SFML.git
    GIT_TAG         2.6.x
    GIT_SHALLOW     ON
    SOURCE_DIR      ${CMAKE_SOURCE_DIR}/SFML
    EXCLUDE_FROM_ALL
    SYSTEM
)

FetchContent_MakeAvailable(SFML)

add_subdirectory(Eris_Log)

add_subdirectory(LeadTheHordes)

### LINKING AND MISC ###

set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT LeadTheHordes)

# Libraries
target_link_directories(LeadTheHordes PRIVATE
    SFML-SOURCE_DIR
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
