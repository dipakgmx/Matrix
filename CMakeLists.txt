cmake_minimum_required(VERSION 3.9)
project(Matrix)

set(CMAKE_CXX_STANDARD 14)
add_compile_options(-Wall -pedantic)

# Create a sources variable with a link to all cpp files to compile
set(SOURCES
        src/main.cpp
        )

# Add an executable with the above sources
add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME}
        PRIVATE
        ${PROJECT_SOURCE_DIR}/include
        )