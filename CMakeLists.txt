cmake_minimum_required(VERSION 3.28)
project(FiniteAutomatas)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "-fsanitize=leak,address,undefined")

include_directories(include)

add_library(AutomatasLib
        src/NFA.cpp
        src/DFA.cpp
)

target_link_directories(AutomatasLib PUBLIC include)

add_executable(MAIN main.cpp)
add_executable(Task2c task2c.cpp)

target_link_libraries(MAIN PRIVATE AutomatasLib)
target_link_libraries(Task2c PRIVATE AutomatasLib)