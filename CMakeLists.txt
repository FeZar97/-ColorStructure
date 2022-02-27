cmake_minimum_required(VERSION 3.20)

set(PROJECT ColorStructure) 
project(${PROJECT} VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(src)
add_subdirectory(tests)

add_executable(${PROJECT} main.cpp)

target_link_libraries(${PROJECT} ColorStructureLib)

install(TARGETS ${PROJECT} DESTINATION bin)