project(tlp-test)

FILE(GLOB_RECURSE all_files
*.cpp
*.cc
*.c++
*.c
*.C)

add_executable(tlp-test ${all_files})
target_link_libraries(tlp-test)
