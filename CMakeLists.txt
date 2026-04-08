cmake_minimum_required(VERSION 3.10)

project(MyHash)

set(CMAKE_CXX_STANDARD 11)

set(SOURCES main.cpp my_hash.cpp)

add_executable(myhash ${SOURCES})