
cmake_minimum_required(VERSION 3.14)

# Project
project(demo.ctp)

MESSAGE(STATUS "CMAKE_SOURCE_DIR = ${CMAKE_SOURCE_DIR}")
MESSAGE(STATUS "CMAKE_BINARY_DIR = ${CMAKE_BINARY_DIR}")



IF (WIN32)
	MESSAGE(STATUS "###########################OS is windows###########################")
	include_directories(
					"${CMAKE_CURRENT_SOURCE_DIR}/../third_party/rapidjson/include"
					"${CMAKE_CURRENT_SOURCE_DIR}/../third_party/brokerapi/6.3.15_20190220_tradeapi64_se_windows"
					)

ELSEIF (UNIX)	
	MESSAGE(STATUS "###########################OS is UNIX-like OS's.###########################")
	
ENDIF ()


link_directories(
	${CMAKE_CURRENT_SOURCE_DIR}/../third_party/brokerapi/6.3.15_20190220_tradeapi64_se_windows
)

set(ctp_collector CtpDaemon.cpp CtpMD.h CtpMD.cpp CtpTD.h CtpTD.cpp)
add_executable(ctp_collector ${ctp_collector})

target_link_libraries(ctp_collector
thostmduserapi_se.lib
thosttraderapi_se.lib
)


