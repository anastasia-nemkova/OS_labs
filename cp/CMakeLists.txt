cmake_minimum_required(VERSION 3.16.3)
set(CMAKE_CXX_STANDARD 17)

add_executable(cp
        sea_battle.cpp
        include/shared_memory.hpp src/shared_memory.cpp
        include/server_utils.hpp src/server_utils.cpp)

target_include_directories(cp PRIVATE include)

add_executable(client
        client.cpp
        include/shared_memory.hpp src/shared_memory.cpp
        include/client_utils.hpp src/client_utils.cpp)

target_include_directories(client PRIVATE include)

find_package(Threads REQUIRED)
target_link_libraries(client PRIVATE pthread)
target_link_libraries(client PRIVATE rt)
        
target_link_libraries(cp PRIVATE rt)
target_link_libraries(cp PRIVATE pthread)


add_dependencies(cp client)