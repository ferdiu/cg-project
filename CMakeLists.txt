cmake_minimum_required(VERSION 3.0)

project(computergraphicsproject)

add_executable(computergraphicsproject main.cpp)

install(TARGETS computergraphicsproject RUNTIME DESTINATION bin)
