cmake_minimum_required(VERSION 3.8)
project(parallelisme_cryptologie)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -g -fdiagnostics-color=auto -std=c++11 -lpthread")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")

set(SOURCE_FILES src/main.cpp)

add_executable(main ${SOURCE_FILES})

find_package(Threads)
target_link_libraries(main ${CMAKE_THREAD_LIBS_INIT})
