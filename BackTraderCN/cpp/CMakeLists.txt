
cmake_minimum_required(VERSION 3.14)

# Project
project(BackTraderCN)

MESSAGE(STATUS "CMAKE_SOURCE_DIR = ${CMAKE_SOURCE_DIR}")
MESSAGE(STATUS "CMAKE_BINARY_DIR = ${CMAKE_BINARY_DIR}")

INCLUDE_DIRECTORIES(third_party/rapidjson/include)
ADD_SUBDIRECTORY("demo.ctp")

ADD_SUBDIRECTORY("test_case")


