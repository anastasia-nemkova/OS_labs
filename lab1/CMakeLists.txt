set(CMAKE_CXX_STANDARD 17)

add_executable(lab1
        main.cpp
        src/parent.cpp
        include/utils.hpp src/utils.cpp)

target_include_directories(lab1 PRIVATE include)

add_executable(child
        src/child.cpp
        include/utils.hpp src/utils.cpp)

target_include_directories(child PRIVATE include)

add_dependencies(lab1 child)