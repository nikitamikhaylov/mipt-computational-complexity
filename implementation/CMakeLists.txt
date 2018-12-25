cmake_minimum_required(VERSION 3.9)
project(implementation)

set(CMAKE_CXX_STANDARD 14)

add_executable(implementation main.cpp BestPerfectMatching.h EulerCircuit.h MST.h test_generation.h)