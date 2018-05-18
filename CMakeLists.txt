cmake_minimum_required(VERSION 3.8)
project(cfg)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES source/main.cpp source/cfg_graph.cpp header/cfg_graph.h source/graph_node.cpp header/graph_node.h source/graph_edge.cpp header/graph_edge.h source/basic_counter.cpp header/basic_counter.h source/utils.cpp header/utils.h)
add_executable(cfg ${SOURCE_FILES})