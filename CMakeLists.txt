cmake_minimum_required(VERSION 3.15)
project(Exercise)

set(CMAKE_CXX_STANDARD 11)
#set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libstdc++ -static-libgcc")

include_directories(.)
include_directories(src)

add_executable(Exercise src/exercise.cpp
        src/Agent.cpp
        src/Agent.h
        src/HomogeneousAgent.cpp
        src/HomogeneousAgent.h
        src/Makefile
        src/RationaleAgent.cpp
        src/RationaleAgent.h
        src/Task.cpp
        src/Task.h)

        
target_link_libraries(Exercise quadmath)