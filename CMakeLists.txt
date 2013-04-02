cmake_minimum_required(VERSION 2.8)
project(MaracujaPackage)

# guard against in-source builds
if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
  message(FATAL_ERROR "In-source builds not allowed. Please make a new directory (called a build directory) and run CMake from there. You may need to remove CMakeCache.txt. ")
endif()

# set some variabiles
set( CMAKE_BUILD_TYPE Debug )
if( NOT WIN32 )
    set( BUILD_SHARED_LIBS TRUE )
endif()

if(NOT EIGEN3_INCLUDE_DIR)
	set(EIGEN3_INCLUDE_DIR /Users/bumuckl/Software/Libs/Eigen3)
endif()

set(QT_INCLUDE_DIR /Library/Frameworks)
set(QT_QMAKE_EXECUTABLE /usr/bin/qmake)

# add lib and app
add_subdirectory( lib )
add_subdirectory( app )
