# CMakeList.txt : CMake project for MHProb, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (MHProb "MHProb.cpp" "MHProb.h" "Monty.h" "Contestant.h")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET MHProb PROPERTY CXX_STANDARD 20)
endif()

#  Old Linux Compat
if (CMAKE_VERSION VERSION_LESS 3.19)
  SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -O2")
endif()

#  Build and Install
install (TARGETS MHProb DESTINATION "${PROJECT_SOURCE_DIR}/rt/bin")
