cmake_minimum_required(VERSION 3.30)
project(graphengine)

set(CMAKE_CXX_STANDARD 14)

add_executable(graphengine main.cpp
        src/impl/graph.cpp
        src/include/graph.h
        src/impl/algorithms.cpp
        src/include/algorithms.h
        src/data_structures/queue.cpp
        src/data_structures/queue.h
        src/data_structures/stack.cpp
        src/data_structures/stack.h
        src/data_structures/minheap.h
        src/impl/io.cpp
        src/include/io.h
        src/impl/spatialgraph.cpp)
