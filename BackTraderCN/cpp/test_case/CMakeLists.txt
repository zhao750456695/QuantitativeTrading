
cmake_minimum_required(VERSION 3.14)

# Project
project(test_case)

MESSAGE(STATUS "CMAKE_SOURCE_DIR = ${CMAKE_SOURCE_DIR}")
MESSAGE(STATUS "CMAKE_BINARY_DIR = ${CMAKE_BINARY_DIR}")



IF (WIN32)
	MESSAGE(STATUS "###########################OS is windows###########################")
	include_directories(
                    ./include
					"${CMAKE_CURRENT_SOURCE_DIR}/../third_party/rapidjson/include"
					)

ELSEIF (UNIX)	
	MESSAGE(STATUS "###########################OS is UNIX-like OS's.###########################")
	
ENDIF ()




set(test_json test_json.cpp)
add_executable(test_json ${test_json})



