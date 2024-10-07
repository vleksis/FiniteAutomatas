cmake_minimum_required(VERSION 3.28)
project(FiniteAutomatas)

set(CMAKE_CXX_STANDARD 20)
SET(CMAKE_CXX_FLAGS "-g -O0 -fprofile-arcs -ftest-coverage --coverage")
SET(CMAKE_C_FLAGS "-g -O0 -fprofile-arcs -ftest-coverage --coverage")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fprofile-arcs -ftest-coverage")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")

include_directories(include)

add_library(AutomatasLib src/NFA.cpp src/DFA.cpp)

target_link_directories(AutomatasLib PUBLIC include)

add_executable(MAIN src/main.cpp)
add_executable(Task2c src/task2c.cpp)

target_link_libraries(MAIN PRIVATE AutomatasLib)
target_link_libraries(Task2c PRIVATE AutomatasLib)

enable_testing()
add_subdirectory(tests)