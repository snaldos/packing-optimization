#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "Coin::Osi" for configuration "Release"
set_property(TARGET Coin::Osi APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(Coin::Osi PROPERTIES
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/lib/libOsi.so.0.108.11"
  IMPORTED_SONAME_RELEASE "libOsi.so.0"
  )

list(APPEND _cmake_import_check_targets Coin::Osi )
list(APPEND _cmake_import_check_files_for_Coin::Osi "${_IMPORT_PREFIX}/lib/libOsi.so.0.108.11" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
