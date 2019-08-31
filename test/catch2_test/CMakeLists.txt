#https://github.com/pantadeusz/hello-catch2-cmake
cmake_minimum_required(VERSION 3.15)
set(CMAKE_CXX_STANDARD 20)


file(GLOB_RECURSE lib_SOURCES "src/*.cpp" "src/*/*.cpp")
add_library(test_base SHARED ${lib_SOURCES})
install (TARGETS test_base DESTINATION lib)

add_subdirectory("wsclient")
add_subdirectory("jadmin_test")
add_subdirectory("juser_test")
add_subdirectory("madmin_test")
add_subdirectory("muser_test")
