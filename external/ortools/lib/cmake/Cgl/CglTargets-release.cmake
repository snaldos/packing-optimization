#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "Coin::Cgl" for configuration "Release"
set_property(TARGET Coin::Cgl APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(Coin::Cgl PROPERTIES
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libCgl.so.0.60.9"
  IMPORTED_SONAME_RELEASE "libCgl.so.0"
  )

list(APPEND _cmake_import_check_targets Coin::Cgl )
list(APPEND _cmake_import_check_files_for_Coin::Cgl "${_IMPORT_PREFIX}/lib/libCgl.so.0.60.9" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
