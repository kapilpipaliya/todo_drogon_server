#https://github.com/pantadeusz/hello-catch2-cmake
cmake_minimum_required(VERSION 3.15)
set(CMAKE_CXX_STANDARD 20)
find_package(Threads REQUIRED)
find_package(ZLIB REQUIRED)
find_package(PostgreSQL REQUIRED)
#find_package(libpqxx REQUIRED)
find_package(Drogon CONFIG REQUIRED)
include_directories(${DROGON_INCLUDE_DIRS})
find_package(fmt REQUIRED)
find_package(Catch2 REQUIRED)
find_package(Poco REQUIRED COMPONENTS Foundation JSON Util XML Zip)

project(muser_test LANGUAGES CXX VERSION 0.0.1)
set(CMAKE_CXX_FLAGS "-std=c++17 -Wall -Wextra")
include_directories("${PROJECT_SOURCE_DIR}/src")

file(GLOB_RECURSE test_SOURCES "*.cpp")

add_executable(muser_test ${test_SOURCES})
target_link_libraries(muser_test test_base Catch2::Catch2
  Threads::Threads
  ZLIB::ZLIB
  PostgreSQL::PostgreSQL
#  libpqxx::pqxx_shared
  ${DROGON_LIBRARIES}
  fmt::fmt
  Poco::Foundation
  )

include(CTest)
include(Catch)
catch_discover_tests(muser_test)
