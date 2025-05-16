cmake_minimum_required(VERSION 3.15)
project(packing_optimization VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${PROJECT_SOURCE_DIR}/src)

# ------------------ JSON ------------------
include(FetchContent)
FetchContent_Declare(
  json
  GIT_REPOSITORY https://github.com/nlohmann/json.git
  GIT_TAG v3.11.2
)
FetchContent_MakeAvailable(json)

# ------------------ OR-TOOLS ------------------
# Try system-wide OR-Tools
find_package(ortools QUIET)

# If not found, try local prebuilt
if(NOT ortools_FOUND)
  message(STATUS "System-wide OR-Tools not found. Trying local prebuilt version.")
  list(APPEND CMAKE_PREFIX_PATH "${CMAKE_SOURCE_DIR}/ortools")

  find_package(ortools QUIET)
endif()

# If still not found, give a clear error
if(NOT ortools_FOUND)
  message(FATAL_ERROR "OR-Tools not found. Please install system-wide or place a prebuilt version in 'ortools/' with 'lib/cmake/ortools/ortoolsConfig.cmake'")
endif()

# ------------------ SOURCES ------------------
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
    src/Algorithms/DP/VectorDPTable.cpp
    src/Algorithms/DP/HashMapDPTable.cpp
    src/Algorithms/APPROX/Greedy.cpp
    src/Algorithms/ILP/ILPBridgePy.cpp
    src/Algorithms/ILP/IntegerLinearProgramming.cpp
    src/Utils.cpp
)

add_definitions(-DPROJECT_DIR="${CMAKE_SOURCE_DIR}")

add_executable(packing_optimization ${SOURCES})

target_link_libraries(packing_optimization
  PRIVATE
    nlohmann_json::nlohmann_json
    ortools::ortools
)

target_compile_options(packing_optimization PRIVATE -Wall -Wextra -Wpedantic)

# ------------------ INSTALL ------------------
install(TARGETS packing_optimization DESTINATION bin)
install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/ DESTINATION include)
