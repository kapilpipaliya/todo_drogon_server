#https://github.com/pantadeusz/hello-catch2-cmake
cmake_minimum_required(VERSION 3.15)
set(CMAKE_CXX_STANDARD 20)


file(GLOB_RECURSE lib_SOURCES "src/*.cpp" "src/*/*.cpp")
add_library(test_base STATIC ${lib_SOURCES}) # SHARED Started giving compile errors
install (TARGETS test_base DESTINATION lib)

target_link_libraries(test_base
  ${DROGON_LIBRARIES}
)

add_subdirectory("wsclient")
add_subdirectory("jadmin_test")
add_subdirectory("juser_test")
add_subdirectory("qmadmin_test")
add_subdirectory("todo_test")
