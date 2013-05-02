#  Try to find Maracuja
#
#  Maracuja_FOUND - System has Maracuja
#  Maracuja_INCLUDE_DIRS - The Maracuja include directories
#  Maracuja_LIBRARY - The libraries needed to use Maracuja
#  Maracuja_DEFINITIONS - Compiler switches required for using Maracuja


# try to find the include dir
find_path( Maracuja_INCLUDE_DIR 
    NAMES
        maracuja/Segmentation.hpp
        maracuja/util.hpp
    PATHS
        $ENV{IRIS_DIR}/include
        ${CMAKE_INSTALL_PREFIX}/include
        /usr/include
        /usr/local/include
        /opt/include
        /opt/local/include
    PATH_SUFFIXES
        maracuja )
        
# find the path to the exported lib files
find_file( Maracuja_DEPENDS Maracuja.cmake
    PATHS
        ${CMAKE_INSTALL_PREFIX}/share
        /usr/share
        /usr/local/share
        /opt/share
        /opt/local/share )

# load all the targets
if( Maracuja_DEPENDS )
    include( "${Maracuja_DEPENDS}" )
else()
    MESSAGE( FATAL_ERROR "Maracuja: not installed.")
endif()

# check if this is a valid component
set( Maracuja_LIBRARY maracuja )
if( TARGET ${Maracuja_LIBRARY} )
    # include the component
    list( APPEND Maracuja_LIBRARIES ${Maracuja_LIBRARY} )
    MESSAGE( STATUS "Maracuja found.")
else()
    MESSAGE( FATAL_ERROR "Maracuja target not available.")
endif()


# set the include dirs
set( Maracuja_INCLUDE_DIRS 
    ${Maracuja_INCLUDE_DIR}
    ${Maracuja_INCLUDE_DIR}/maracuja )
    
    


