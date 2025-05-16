cmake_minimum_required(VERSION 3.15)
project(packing_optimization VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(${PROJECT_SOURCE_DIR}/src)

# ------------------ JSON LIBRARY ------------------
include(FetchContent)

FetchContent_Declare(
  json
  GIT_REPOSITORY https://github.com/nlohmann/json.git
  GIT_TAG v3.11.2
)
FetchContent_MakeAvailable(json)

# ------------------ OR-TOOLS SYSTEM CHECK ------------------
set(ORTOOLS_FOUND FALSE)
find_package(ortools QUIET)
if(ortools_FOUND)
  message(STATUS "Found system-wide OR-Tools.")
  set(USE_SYSTEM_ORTOOLS TRUE)
else()
  message(WARNING "System-wide OR-Tools not found. Building OR-Tools locally.")
  set(USE_SYSTEM_ORTOOLS FALSE)
  include(ExternalProject)
  set(ORTOOLS_INSTALL_DIR ${CMAKE_BINARY_DIR}/ortools-install)

  ExternalProject_Add(
    ortools_external
    PREFIX ${CMAKE_BINARY_DIR}/_deps/ortools
    GIT_REPOSITORY https://github.com/google/or-tools.git
    GIT_TAG v9.8
    CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${ORTOOLS_INSTALL_DIR}
               -DBUILD_DEPS=ON
               -DBUILD_PYTHON=OFF
               -DBUILD_EXAMPLES=OFF
    UPDATE_DISCONNECTED 1
  )

  # Try finding it again in the install dir
  list(APPEND CMAKE_PREFIX_PATH "${ORTOOLS_INSTALL_DIR}")
  find_package(ortools REQUIRED PATHS ${ORTOOLS_INSTALL_DIR})
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

# If OR-Tools is being built locally, add dependency
if(NOT USE_SYSTEM_ORTOOLS)
  add_dependencies(packing_optimization ortools_external)
endif()

target_link_libraries(packing_optimization
  PRIVATE
    nlohmann_json::nlohmann_json
    ortools::ortools
)

target_compile_options(packing_optimization PRIVATE -Wall -Wextra -Wpedantic)

# ------------------ INSTALL RULES ------------------
install(TARGETS packing_optimization DESTINATION bin)
install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/ DESTINATION include)
