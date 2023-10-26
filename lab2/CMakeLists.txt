set(CMAKE_CXX_STANDARD 17)

set(THREADS_PREFER_PTHREAD_FLAG ON)

add_executable(lab2 main.cpp src/bitonic-sort.cpp include/bitonic-sort.hpp)

target_include_directories(lab2 PRIVATE include)

target_link_libraries(lab2 PRIVATE Threads::Threads)

