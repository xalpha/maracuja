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


cmake_minimum_required(VERSION 2.8)
project(Maracuja CXX)

# guard against in-source builds
if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
  message(FATAL_ERROR "In-source builds not allowed. Please make a new directory (called a build directory) and run CMake from there. You may need to remove CMakeCache.txt. ")
endif()

# configure the project
include( MaracujaConfig.cmake )

# add the include files
list( APPEND Maracuja_INC
    include/maracuja/MSImage.hpp
    include/maracuja/Spectrum.hpp
    include/maracuja/Channel.hpp
	include/maracuja/SpecOps.hpp
    include/maracuja/util.hpp )
list( APPEND Maracuja_SRC
    src/MSImage.cpp
    src/Spectrum.cpp
    src/Channel.cpp 
	src/SpecOps.cpp )

# external dependencies of maracuja
list( APPEND Maracuja_EXTERN_INC
    extern/cimg/CImg.h
    extern/tinyxml2/tinyxml2.h )
list( APPEND Maracuja_EXTERN_SRC
    extern/tinyxml2/tinyxml2.cpp )

# set include directories
include_directories( ${Maracuja_INCLUDE_DIRS} )

# add library
add_library( ${Maracuja_TARGET} ${Maracuja_INC} ${Maracuja_SRC} ${Maracuja_EXTERN_INC} ${Maracuja_EXTERN_SRC} )
target_link_libraries( ${Maracuja_TARGET} ${Maracuja_LINK_LIBRARIES} )

# configure target
set_target_properties(${Maracuja_TARGET}
    PROPERTIES
        PUBLIC_HEADER "${Maracuja_INC}"
        COMPILE_DEFINITIONS "${Maracuja_COMPILE_DEFINITIONS}"
        COMPILE_FLAGS "${Maracuja_COMPILE_FLAGS}"
        LINK_FLAGS "${Maracuja_LINK_FLAGS}" )

export( TARGETS ${Maracuja_TARGET} FILE "${CMAKE_BINARY_DIR}/Maracuja_Depends.cmake")

# install the lib's binary and headers
install(TARGETS ${Maracuja_TARGET}
        EXPORT Maracuja
        RUNTIME DESTINATION "bin"
        LIBRARY DESTINATION "lib"
        ARCHIVE DESTINATION "lib"
        PUBLIC_HEADER DESTINATION "include/maracuja" )

# install targets
install(EXPORT Maracuja DESTINATION share )

# install module finder
install(FILES "${CMAKE_CURRENT_LIST_DIR}/FindMaracuja.cmake" DESTINATION share )

# install extern headers
install(FILES ${Maracuja_EXTERN_INC} DESTINATION "include" )


# add test app
add_executable( test test/test.cpp )
target_link_libraries( test ${Maracuja_TARGET} )

