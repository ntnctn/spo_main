# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Release")
  file(REMOVE_RECURSE
  "CMakeFiles\\ReadPP_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\ReadPP_autogen.dir\\ParseCache.txt"
  "ReadPP_autogen"
  )
endif()
