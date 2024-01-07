include(FetchContent)

FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG        release-1.11.0
)

FetchContent_MakeAvailable(googletest)
add_library(GTest::GTest INTERFACE IMPORTED)
target_link_libraries(GTest::GTest INTERFACE gtest_main)


set(CMAKE_CXX_STANDARD 17)

#add LAB1

add_executable(lab1_test lab1_test.cpp ../lab1/src/parent.cpp ../lab1/include/parent.hpp
        ../lab1/src/utils.cpp ../lab1/include/utils.hpp)

target_link_libraries(lab1_test PRIVATE GTest::GTest)
target_include_directories(lab1_test PRIVATE ../lab1/include)

add_test(lab1_test lab1_test)

#add LAB2

add_executable(lab2_test lab2_test.cpp ../lab2/src/bitonic-sort.cpp ../lab2/include/bitonic-sort.hpp)

target_link_libraries(lab2_test PRIVATE GTest::GTest)
target_include_directories(lab2_test PRIVATE ../lab2/include)

add_test(lab2_test lab2_test)

#add LAB3

add_executable(lab3_test lab3_test.cpp ../lab3/src/parent.cpp ../lab3/include/parent.hpp
        ../lab3/src/utils.cpp ../lab3/include/utils.hpp)

target_link_libraries(lab3_test PRIVATE GTest::GTest)
target_include_directories(lab3_test PRIVATE ../lab3/include)
target_link_libraries(lab3_test PRIVATE pthread)
target_link_libraries(lab3_test PRIVATE rt)

add_test(lab3_test lab3_test)

#add LAB4

add_executable(lab4_realiz1_test lab4_realiz1_test.cpp ../lab4/include/realizations.hpp ../lab4/src/realization1.cpp)
target_link_libraries(lab4_realiz1_test PRIVATE GTest::GTest)
target_include_directories(lab4_realiz1_test PRIVATE ../lab4/include)

add_test(lab4_realiz1_test lab4_realiz1_test)

add_executable(lab4_realiz2_test lab4_realiz2_test.cpp ../lab4/include/realizations.hpp ../lab4/src/realization2.cpp)
target_link_libraries(lab4_realiz2_test PRIVATE GTest::GTest)
target_include_directories(lab4_realiz2_test PRIVATE ../lab4/include)

add_test(lab4_realiz2_test lab4_realiz2_test)

# Lab 5-7

set(CMAKE_CXX_FLAGS "-lzmq")

add_executable(lab5-7_test lab5-7_test.cpp ../lab5-7/src/topology.cpp ../lab5-7/src/socket.cpp)
target_link_libraries(lab5-7_test PRIVATE GTest::GTest)
target_include_directories(lab5-7_test PRIVATE ../lab5-7/include)

target_link_libraries(lab5-7_test PRIVATE zmq)

add_test(lab5-7_test lab5-7_test)

# CP

add_executable(cp_test cp_test.cpp ../cp/src/server_utils.cpp ../cp/include/server_utils.hpp
        ../cp/src/client_utils.cpp ../cp/include/client_utils.hpp
        ../cp/src/shared_memory.cpp ../cp/include/shared_memory.hpp)

target_link_libraries(cp_test PRIVATE GTest::GTest)
target_include_directories(cp_test PRIVATE ../cp/include)
target_link_libraries(cp_test PRIVATE pthread)
target_link_libraries(cp_test PRIVATE rt)

add_test(cp_test cp_test)