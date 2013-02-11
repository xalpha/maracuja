###############################################################################
#                                                                             #
# This file is part of maracuja, a C++ library for multispectral images       #
#                                                                             #
# Copyright (C) 2012 Alexandru Duliu, Anne-Claire Morvan                      #
#                                                                             #
# maracuja is free software; you can redistribute it and/or                   #
# modify it under the terms of the GNU Lesser General Public                  #
# License as published by the Free Software Foundation; either                #
# version 3 of the License, or (at your option) any later version.            #
#                                                                             #
# maracuja is distributed in the hope that it will be useful, but WITHOUT ANY #
# WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS   #
# FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License or the  #
# GNU General Public License for more details.                                #
#                                                                             #
# You should have received a copy of the GNU Lesser General Public            #
# License along with maracuja. If not, see <http://www.gnu.org/licenses/>.    #
#                                                                             #
###############################################################################

# Config file for the maracuja library
# It defines the following variables
#
# Maracuja_INCLUDE_DIR - include directory for maracuja headers
# Maracuja_INCLUDE_DIRS - all include directories maracuja needs
# Maracuja_LIBRARY - library

# version
set(Maracuja_MAJOR_VERSION 0)
set(Maracuja_MINOR_VERSION 1)
set(Maracuja_PATCH_VERSION 0)
set(Maracuja_VERSION ${Maracuja_MAJOR_VERSION}.${Maracuja_MINOR_VERSION}.${Maracuja_PATCH_VERSION})

# set path
set( Maracuja_DIR ${CMAKE_CURRENT_LIST_DIR})
set( ENV{Maracuja_DIR} ${Maracuja_DIR} )

# add module paths
list( APPEND CMAKE_MODULE_PATH ${Maracuja_DIR}/cmake ${CMAKE_INSTALL_PREFIX}/share $ENV{HOME}/.local/share )

# find Eigen3
if( WIN32 )
    set( EIGEN3_INCLUDE_DIR $ENV{Eigen3_DIR} )
endif()
find_package( Eigen3 REQUIRED )

# set the include dir
set( Maracuja_INCLUDE_DIR "${Maracuja_DIR}/include")

# set target names
set( Maracuja_TARGET maracuja )

# set compile definitions
set( Maracuja_COMPILE_DEFINITIONS LIME CACHE INTERNAL "all compile definitions maracuja needs"  )

# if this is 32-bit, disable alignment
if( NOT CMAKE_SIZEOF_VOID_P MATCHES "8")
    list( APPEND Maracuja_COMPILE_DEFINITIONS EIGEN_DONT_ALIGN)
endif()

# set linker flags
if( WIN32 )
	list( APPEND Maracuja_LINK_FLAGS " /MANIFEST:NO" )
endif()


# set library paths
set( Maracuja_LIBRARY ${Maracuja_TARGET} CACHE INTERNAL "the maracuja lib" )

# set include directories
set( Maracuja_INCLUDE_DIRS
    ${Maracuja_INCLUDE_DIR}
    ${Maracuja_DIR}/extern/cimg
    ${Maracuja_DIR}/extern/tinyxml2
    ${EIGEN3_INCLUDE_DIR} CACHE INTERNAL "all include directories maracuja needs" )

# link libraries
set( Maracuja_LINK_LIBRARIES
    -lm
    -lc CACHE INTERNAL "all libs maracuja needs" )


# enable C++11 support
if( NOT WIN32 )
    if( CMAKE_COMPILER_IS_GNUCXX )
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --std=c++0x")
    else( CMAKE_COMPILER_IS_GNUCXX )
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Qunused-arguments")
    endif()
endif()

# try to find OpenMP
find_package( OpenMP )
if(OPENMP_FOUND)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
    add_definitions( -DMARACUJA_OPENMP )
    #list( APPEND Iris_COMPILE_DEFINITIONS IRIS_OPENMP )
    #list( APPEND Iris_LINK_LIBRARIES ${OpenMP_CXX_FLAGS} )
    #list( APPEND Iris_LINK_FLAGS ${OpenMP_EXE_LINKER_FLAGS} )
    message( STATUS "maracuja: OpenMP detected, taking advantage" )
endif()
