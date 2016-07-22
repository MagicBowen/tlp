cmake_minimum_required(VERSION 2.8)

project("tlp")

if(UNIX)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-invalid-offsetof  -g -std=c++11")
endif()

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include")

if(ENABLE_TEST)
  add_subdirectory(test)
endif()

install(DIRECTORY include/tlp DESTINATION include)


