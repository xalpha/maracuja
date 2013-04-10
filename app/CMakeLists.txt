##############################################################################
#                                                                            #
# This file is part of MaracujaMS, a C++ UI image segmentation               #
#                                                                            #
# Copyright (C) 2013 Alexandru Duliu, Anne-Claire Morvan                     #
#                                                                            #
# MaracujaMS is free software; you can redistribute it and/or                #
# modify it under the terms of the GNU  General Public License               #
# as published by the Free Software Foundation; either version 3             #
# of the License, or (at your option) any later version.                     #
#                                                                            #
# MaracujaMS is distributed in the hope that it will be useful,              #
# but WITHOUT ANY WARRANTY; without even the implied warranty of             #
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the              #
# GNU General Public License for more details.                               #
#                                                                            #
# You should have received a copy of the GNU General Public License          #
# along with MaracujaMS. If not, see <http://www.gnu.org/licenses/>.         #
#                                                                            #
##############################################################################


cmake_minimum_required(VERSION 2.8)
project( MaracujaMS CXX )

# add module paths
list( APPEND CMAKE_MODULE_PATH
    ${Maracuja_DIR}/cmake
    ${CMAKE_INSTALL_PREFIX}/share
    ${CMAKE_CURRENT_LIST_DIR}/cmake
    $ENV{HOME}/.local/share )

# find Qt
if( WIN32 )
    set( QT_QMAKE_EXECUTABLE "$ENV{Qt_DIR}/bin/qmake.exe" )
endif()
find_package( Qt4 COMPONENTS QtCore QtGui QtXml )


# some more qt stuff
include(${QT_USE_FILE})
add_definitions(${QT_DEFINITIONS})

# QCustomPlot (way smaller than QWT)
set( Q_CUSTOM_PLOT_INC extern/qcustomplot/qcustomplot.h )
set( Q_CUSTOM_PLOT_SRC extern/qcustomplot/qcustomplot.cpp )

# set the target
set( MaracujaMS_Target maracujams )

# set the header files of QObject derived classes
set( MaracujaMS_INC include/MaracujaMS.hpp )
set( MaracujaMS_SRC 
    src/MaracujaMS.cpp
    src/main.cpp 
    src/SSM.cpp 
    src/SpecOpsTest.cpp )
set( MaracujaMS_QT_UI ui/MaracujaMS.ui )
set( MaracujaMS_QT_RES res/MaracujaMS.qrc )

# set include directories
set( MaracujaMS_INCLUDE_DIRS
    include
    extern/qcustomplot
    ${Maracuja_INCLUDE_DIRS}
    $ENV{HOME}/.local/include
    ${CMAKE_CURRENT_BINARY_DIR} )

# set link libraries
set( MaracujaMS_LINK_LIBS
    ${QT_LIBRARIES}
    ${Maracuja_LIBRARY} )

# set compile definitions
set( MaracujaMS_COMPILE_DEFINITIONS
    ${Maracuja_COMPILE_DEFINITIONS}
    QT_NO_DEPRECATED
    _USE_MATH_DEFINES )

# run the qt moc & uic
QT4_ADD_RESOURCES( MaracujaMS_QT_RES_SRC ${MaracujaMS_QT_RES})
QT4_WRAP_CPP( MaracujaMS_QT_HPP_MOC
    ${MaracujaMS_INC}
    ${Q_CUSTOM_PLOT_INC} )
QT4_WRAP_UI( MaracujaMS_QT_UI_UIC ${MaracujaMS_QT_UI} )

# set include paths
include_directories( ${MaracujaMS_INCLUDE_DIRS} )

# add the exec
add_executable( ${MaracujaMS_Target}
    ${MaracujaMS_SRC}
    ${MaracujaMS_INC}
    ${MaracujaMS_QT_HPP_MOC}
    ${MaracujaMS_QT_UI_UIC}
    ${MaracujaMS_QT_RES_SRC}
    ${Q_CUSTOM_PLOT_INC}
    ${Q_CUSTOM_PLOT_SRC} )

# enable C++11 support
if( NOT WIN32 )
    if( CMAKE_COMPILER_IS_GNUCXX )
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --std=c++0x")
    else( CMAKE_COMPILER_IS_GNUCXX )
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Qunused-arguments")
    endif()
endif()

# set link libraries
target_link_libraries( ${MaracujaMS_Target} ${MaracujaMS_LINK_LIBS} )

# configure target
set_target_properties(${MaracujaMS_Target}
    PROPERTIES
        PUBLIC_HEADER "${MaracujaMS_INC}"
        COMPILE_DEFINITIONS "${MaracujaMS_COMPILE_DEFINITIONS}"
        COMPILE_FLAGS "${Maracuja_COMPILE_FLAGS}"
        LINK_FLAGS "${Maracuja_LINK_FLAGS}" )
