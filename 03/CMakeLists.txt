cmake_minimum_required(VERSION 3.16)

project(DataStructureExperiment3 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(test_kmp
    tests/test_kmp.cpp    
)

target_include_directories(test_kmp PRIVATE include)



