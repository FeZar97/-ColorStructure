cmake_minimum_required(VERSION 3.20)

project(ColorStructure VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(ColorStructure main.cpp)

add_subdirectory(src)
add_subdirectory(tests)

target_link_libraries(ColorStructure ColorStructureLib)

install(TARGETS ColorStructure DESTINATION bin)