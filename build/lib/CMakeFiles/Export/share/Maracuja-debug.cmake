#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
SET(CMAKE_IMPORT_FILE_VERSION 1)

# Compute the installation prefix relative to this file.
GET_FILENAME_COMPONENT(_IMPORT_PREFIX "${CMAKE_CURRENT_LIST_FILE}" PATH)
GET_FILENAME_COMPONENT(_IMPORT_PREFIX "${_IMPORT_PREFIX}" PATH)

# Import target "maracuja" for configuration "Debug"
SET_PROPERTY(TARGET maracuja APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
SET_TARGET_PROPERTIES(maracuja PROPERTIES
  IMPORTED_LINK_INTERFACE_LIBRARIES_DEBUG "-lm;-lc"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/lib/libmaracuja.dylib"
  IMPORTED_SONAME_DEBUG "libmaracuja.dylib"
  )

# Cleanup temporary variables.
SET(_IMPORT_PREFIX)

# Commands beyond this point should not need to know the version.
SET(CMAKE_IMPORT_FILE_VERSION)
