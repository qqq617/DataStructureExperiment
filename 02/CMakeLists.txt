cmake_minimum_required(VERSION 3.16)

project(DataStructureExperiment2 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


add_executable(maze_app
    main.cpp
    src/maze_solver.cpp
)

target_include_directories(maze_app PRIVATE include)