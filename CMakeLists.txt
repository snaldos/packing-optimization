cmake_minimum_required(VERSION 3.10)
project(packing_optimization VERSION 1.0)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include directories
include_directories(${PROJECT_SOURCE_DIR}/src)

# Source files
set(SOURCES
    src/main.cpp
    src/Parser/CSVParser.cpp
    src/Parser/ParserUtils.cpp
    src/Batch/BatchStateManager.cpp
    src/Batch/BatchDataSetManager.cpp
    src/Batch/BatchInputManager.cpp
    src/DataStructures/Pallet.cpp
    src/DataStructures/Truck.cpp
)
file(COPY ${PROJECT_SOURCE_DIR}/data DESTINATION ${CMAKE_BINARY_DIR})

# Copy input files to build directory
file(COPY ${PROJECT_SOURCE_DIR}/input DESTINATION ${CMAKE_BINARY_DIR})

# Preprocessor definition to get project directory at runtime
add_definitions(-DPROJECT_DIR="${CMAKE_SOURCE_DIR}")

# Create executable
add_executable(packing_optimization ${SOURCES})

# Install targets
install(TARGETS packing_optimization DESTINATION bin)
install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/ DESTINATION include)
