cmake_minimum_required(VERSION 3.16)
project(GeneticPong CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

add_executable(GeneticPong
    src/Main.cpp
    src/GeneticPong.cpp
    src/Generation.cpp
    src/Paddle.cpp
    src/Ball.cpp
)

target_include_directories(GeneticPong PRIVATE include)

target_link_libraries(GeneticPong PRIVATE sfml-graphics sfml-window sfml-system)
