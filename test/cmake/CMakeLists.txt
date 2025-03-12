#this is the current version on my system.  Other version may work
cmake_minimum_required(VERSION 3.28)


#noeabi should mostly support this
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
#use the gnu standard
set(CMAKE_CXX_EXTENSIONS ON)

# Define the build type, DEBUG by default
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "DEBUG")
endif()

# Set the project name
set(CMAKE_PROJECT_NAME boot)

# Include toolchain file
include("arm-none-eabi.cmake")

# Enable compile command to ease indexing with e.g. clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

# Enable CMake support for ASM and C languages
enable_language(CXX C ASM)

# Core project settings
project(${CMAKE_PROJECT_NAME})
message("Build type: " ${CMAKE_BUILD_TYPE})

# Create an executable object type
add_executable(${CMAKE_PROJECT_NAME})
#include the cmake file for the bootlib
add_subdirectory(bootLib/)

# Add sources to executable
FILE(GLOB SOURCES "../src/*.cpp")
target_sources(${CMAKE_PROJECT_NAME} PRIVATE
${SOURCES}
    # Add user sources here
)

# Add linked libraries
target_link_libraries(${CMAKE_PROJECT_NAME}
    bootLib

    # Add user defined libraries
)
#stolen from stackoverflow, generates dependency graph
add_custom_target(graphviz ALL
    COMMAND ${CMAKE_COMMAND} "--graphviz=graphviz.dot" .
    COMMAND dot -Tpng graphviz.dot -o graphviz.png
    WORKING_DIRECTORY "${CMAKE_BINARY_DIR}"
)
