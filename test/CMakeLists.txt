cmake_minimum_required(VERSION 3.15.1)
project(test1)
#set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake_modules/)

find_package(PostgreSQL)
find_package(libpqxx REQUIRED)

find_package (Jsoncpp REQUIRED)
#find_package(folly)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
SET(CMAKE_AUTOUIC ON)
find_package(Qt5 COMPONENTS Core Gui Widgets Network Xml Sql REQUIRED)

find_package(Catch2 REQUIRED)
# Profiling the test execution duration
#https://github.com/catchorg/Catch2/issues/974#issuecomment-319584639
#https://github.com/catchorg/Catch2/blob/master/docs/reporters.md

set(JEWEL_HDR
  mainwindow.h
)

set(JEWEL_SRC
  mainwindow.cpp
  mainwindow.ui
  main.cpp
)

#set(JEWEL_RESOURCES
#    languages.qrc
#)
include_directories(..)

add_executable(${PROJECT_NAME}
    ${JEWEL_HDR}
    ${JEWEL_SRC}
#    ${JEWEL_RESOURCES}
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
    PostgreSQL::PostgreSQL
    libpqxx::pqxx_shared
    libjewelconnection
    ${JSONCPP_LIBRARY}
#    folly.a
#    folly
  Qt5::Core
  Qt5::Gui
  Qt5::Widgets
  Qt5::Network
  Qt5::Xml
  Qt5::Sql

    Catch2::Catch2
)
add_subdirectory("hello-catch2-cmake")
