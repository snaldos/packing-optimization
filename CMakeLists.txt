cmake_minimum_required(VERSION 3.10)
project(packing_optimization VERSION 1.0)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include directories
include_directories(${PROJECT_SOURCE_DIR}/src)

# Source files
set(SOURCES
    src/RoutePlanning/location.cpp
    src/RoutePlanning/route.cpp
    src/DataStructures/UFDS.cpp
    src/main.cpp
    src/BatchProcessor/BatchProcessor.cpp
    src/BatchProcessor/BatchDataSetManager.cpp
    src/BatchProcessor/BatchInputManager.cpp
    src/RoutePlanning/RouteProcessor.cpp
    src/PalletPacking/DataStructures/Pallet.cpp
    src/PalletPacking/DataStructures/Truck.cpp
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
