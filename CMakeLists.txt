cmake_minimum_required(VERSION 3.11)

project (rs-udprelay C CXX)

#SET(Boost_USE_STATIC_LIBS on)
find_package(Boost 1.66 REQUIRED system)

find_package(Threads)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

SET(CMAKE_CXX_STANDARD 11)
#SET(CMAKE_CXX_FLAGS "-Wall -Wextra")
#SET(CMAKE_CXX_FLAGS_DEBUG "-g")
#SET(CMAKE_CXX_FLAGS_RELEASE "-Os -DNDEBUG")

#SET(CMAKE_FINDBRARY_SUFFIXES ".a")
#SET(BUILD_SHARED_LIBS OFF)
#SET(CMAKE_EXE_LINKER_FLAGS "-static")

#SUBDIRS(shalib)

include_directories(${Boost_INCLUDE_DIRS})

add_executable (udprelay
	src/udprelay.cpp
)

TARGET_LINK_LIBRARIES(udprelay
    ${CMAKE_THREAD_LIBS_INIT}
    ${Boost_LIBRARIES}
)

set_property(TARGET udprelay PROPERTY INTERPROCEDURAL_OPTIMIZATION True)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/src/udprelay.sh ${CMAKE_CURRENT_BINARY_DIR}/udprelay.sh COPYONLY)
