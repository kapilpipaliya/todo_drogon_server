#https://github.com/pantadeusz/hello-catch2-cmake
cmake_minimum_required(VERSION 3.15)
set(CMAKE_CXX_STANDARD 20)
find_package(Threads REQUIRED)
find_package(ZLIB REQUIRED)
find_package (UUID REQUIRED)
find_package(PostgreSQL REQUIRED)
#find_package(libpqxx REQUIRED)
find_package(Drogon CONFIG REQUIRED)
include_directories(${DROGON_INCLUDE_DIRS})
find_package(fmt REQUIRED)
find_package(Catch2 REQUIRED)
find_package(Poco REQUIRED COMPONENTS Foundation JSON Util XML Zip)

project(hello-catch2-cmake LANGUAGES CXX VERSION 0.0.1)
set(CMAKE_CXX_FLAGS "-std=c++17 -Wall -Wextra")
include_directories("${PROJECT_SOURCE_DIR}/src")
file(GLOB_RECURSE lib_SOURCES "src/*.cpp" "src/*/*.cpp")
file(GLOB_RECURSE test_SOURCES "test/*.cpp")
add_library(fibonacci SHARED ${lib_SOURCES})
install (TARGETS fibonacci DESTINATION lib)



add_executable(hello-catch2-cmake-test ${test_SOURCES})
target_link_libraries(hello-catch2-cmake-test fibonacci Catch2::Catch2
  Threads::Threads
  ZLIB::ZLIB
  ${UUID_LIBRARY}
  PostgreSQL::PostgreSQL
#  libpqxx::pqxx_shared
  ${DROGON_LIBRARIES}
  fmt::fmt
  Poco::Foundation
  )

include(CTest)
include(Catch)
catch_discover_tests(hello-catch2-cmake-test)
