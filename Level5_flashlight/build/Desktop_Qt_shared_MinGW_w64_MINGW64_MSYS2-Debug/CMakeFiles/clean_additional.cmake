# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\Level5_flashlight_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\Level5_flashlight_autogen.dir\\ParseCache.txt"
  "Level5_flashlight_autogen"
  )
endif()
