cmake_minimum_required(VERSION 3.30)
project(graphengine)

set(CMAKE_CXX_STANDARD 14)

add_executable(graphengine main.cpp
        src/graph.cpp
        src/graph.h
        src/algorithms.cpp
        src/algorithms.h
        src/data_structures/queue.cpp
        src/data_structures/queue.h
        src/data_structures/stack.cpp
        src/data_structures/stack.h
        src/data_structures/minheap.cpp
        src/data_structures/minheap.h
        src/io.cpp
        src/io.h)
