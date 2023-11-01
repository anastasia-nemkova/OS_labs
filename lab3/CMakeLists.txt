cmake_minimum_required(VERSION 3.16.3)
set(CMAKE_CXX_STANDARD 17)

add_executable(lab3
        main.cpp
        src/parent.cpp
        include/utils.hpp src/utils.cpp)

target_include_directories(lab3 PRIVATE include)

add_executable(child3
        src/child.cpp
        include/utils.hpp src/utils.cpp)

target_include_directories(child3 PRIVATE include)

find_package(Threads REQUIRED)
target_link_libraries(child3 PRIVATE pthread)
target_link_libraries(child3 PRIVATE rt)
        
target_link_libraries(lab3 PRIVATE rt)
target_link_libraries(lab3 PRIVATE pthread)


add_dependencies(lab3 child3)