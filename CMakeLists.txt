cmake_minimum_required(VERSION 2.8)
project(parallelisme_cryptologie)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -g -std=c++11")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Ofast -march=native")

set(SOURCE_FILES src/main.cpp)

add_executable(main ${SOURCE_FILES})

find_package(Threads)
target_link_libraries(main ${CMAKE_THREAD_LIBS_INIT})
