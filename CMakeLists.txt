cmake_minimum_required(VERSION 3.10)
project(packing_optimization VERSION 1.0)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include directories
include_directories(${PROJECT_SOURCE_DIR}/src)

include(FetchContent)

FetchContent_Declare(
  json
  GIT_REPOSITORY https://github.com/nlohmann/json.git
  GIT_TAG v3.11.2  # or latest
)

FetchContent_MakeAvailable(json)

# Source files
set(SOURCES
    src/main.cpp
    src/Parser/ParserUtils.cpp
    src/Parser/CSVParser.cpp
    src/Batch/BatchUtils.cpp
    src/Batch/BatchStateManager.cpp
    src/Batch/BatchDataSetManager.cpp
    src/Batch/BatchInputManager.cpp
    src/DataStructures/Pallet.cpp
    src/DataStructures/Truck.cpp
    src/Algorithms/BF/BruteForce.cpp
    src/Algorithms/DP/DynamicProgramming.cpp
    src/Algorithms/APPROX/Greedy.cpp
    src/Algorithms/ILP/ILPBridge.cpp
    src/Utils.cpp
)

# Preprocessor definition to get project directory at runtime
add_definitions(-DPROJECT_DIR="${CMAKE_SOURCE_DIR}")

# Create executable
add_executable(packing_optimization ${SOURCES})

# Install targets
install(TARGETS packing_optimization DESTINATION bin)
install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/ DESTINATION include)

target_link_libraries(packing_optimization PRIVATE nlohmann_json::nlohmann_json)
