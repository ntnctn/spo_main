# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\spo_main_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\spo_main_autogen.dir\\ParseCache.txt"
  "spo_main_autogen"
  )
endif()
