cmake_minimum_required(VERSION 2.8)

project("tlp")

set(ENABLE_TEST   OFF CACHE BOOL "Enable the test")
set(ENABLE_SAMPLE OFF CACHE BOOL "Enable the smaple")

if(UNIX)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-invalid-offsetof  -g -std=c++11")
endif()

set(TLP_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")

include_directories("${TLP_INCLUDE_DIR}")

if(ENABLE_TEST)
  add_subdirectory(test)
endif()

if(ENABLE_SAMPLE)
  add_subdirectory(samples)
endif()

install(DIRECTORY include/tlp DESTINATION include)
