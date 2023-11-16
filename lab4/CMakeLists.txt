cmake_minimum_required(VERSION 3.16.3)
project(lab4)

add_library(realization1 SHARED src/realization1.cpp)
add_library(realization2 SHARED src/realization2.cpp)

set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/lab4/include)

target_include_directories(realization1 PUBLIC ${INCLUDE_DIR})
target_include_directories(realization2 PUBLIC ${INCLUDE_DIR})

add_executable(static_main static_main.cpp)
add_executable(dynamic_main dynamic_main.cpp)

target_link_libraries(static_main PRIVATE realization1)

target_link_libraries(dynamic_main dl)

target_include_directories(dynamic_main PRIVATE ${INCLUDE_DIR})