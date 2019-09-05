cmake_minimum_required (VERSION 3.15)

## This includes the Vita toolchain, must go before project definition
# It is a convenience so you do not have to type
# -DCMAKE_TOOLCHAIN_FILE=$VITASDK/share/vita.toolchain.cmake for cmake. It is
# highly recommended that you include this block for all projects.

#if(NOT DEFINED CMAKE_TOOLCHAIN_FILE)
#  if(DEFINED ENV{HOME})
#    set(CMAKE_TOOLCHAIN_FILE "$ENV{HOME}/k/cpp_stuff/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE PATH "toolchain file")
#  else()
#    message(FATAL_ERROR "$ENV{HOME}/k/cpp_stuff/vcpkg/scripts/buildsystems/vcpkg.cmake vcpkg path wrong!")
#  endif()
#endif()


Project(jdragon)

include_directories("$ENV{HOME}/k/cpp_stuff/vcpkg/installed/x64-linux/include")

set(CMAKE_CXX_STANDARD 20)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

include(CheckIncludeFileCXX)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(Drogon CONFIG REQUIRED)
include_directories(${DROGON_INCLUDE_DIRS})
#link_libraries(${DROGON_LIBRARIES})

set(THREADS_PREFER_PTHREAD_FLAG TRUE)
find_package(Threads REQUIRED)

remove_definitions(USE_MYSQL)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall ${CMAKE_CXX_STD_FLAGS}")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall ${CMAKE_CXX_STD_FLAGS}")

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake_modules/ "$ENV{HOME}/k/cpp_stuff/actor-framework/cmake/")
find_package(Boost REQUIRED COMPONENTS filesystem date_time system timer )

#find_package (UUID REQUIRED)

find_package (OpenSSL)
if(OpenSSL_FOUND)
    list(APPEND _OPTIONAL_LIBS OpenSSL::SSL OpenSSL::Crypto)
endif()

find_package(ZLIB REQUIRED)

find_package(PostgreSQL REQUIRED)

find_package (SQLite3)
if (SQLITE3_FOUND)
  include_directories(${SQLITE3_INCLUDE_DIRS})
  link_libraries(${SQLITE3_LIBRARIES})
endif()

# find_package(Boost REQUIRED COMPONENTS chrono filesystem date_time program_options iostreams)
set (Boost_ARCHITECTURE "-x64")
# find_package(Boost REQUIRED COMPONENTS filesystem date_time system timer)
#find_package(cppzmq REQUIRED)
find_package(PNG REQUIRED)
find_package(Threads REQUIRED)
find_package(OpenSSL REQUIRED)
#find_package(GDAL REQUIRED)
#find_package(msgpack REQUIRED)
find_package(fmt REQUIRED)

#find_package(Poco REQUIRED COMPONENTS Foundation JSON Util XML Zip)
#find_package(TBB REQUIRED) # Intel(R) Threading Building Blocks (Intel TBB)
#find_package(Angelscript REQUIRED)
#find_package(easyloggingpp REQUIRED)
#find_package(RapidJSON REQUIRED) # no need

find_package(CAF COMPONENTS core io REQUIRED )
#find_package(HighFive 2.0 REQUIRED)
#https://abseil.io/docs/cpp/quickstart-cmake
#git clone https://github.com/abseil/abseil-cpp.git
# Process Abseil's CMake build system
#add_subdirectory(abseil-cpp)
#find_package(Wt REQUIRED Wt HTTP)

AUX_SOURCE_DIRECTORY(./ SRC_DIR)
AUX_SOURCE_DIRECTORY(wscontroller WSCTL_SRC)
AUX_SOURCE_DIRECTORY(wscontroller/context WSCTL_SRC_CONTEXT)
AUX_SOURCE_DIRECTORY(httpcontroller HTTPCTL_SRC)
AUX_SOURCE_DIRECTORY(actor ACTOR_SRC)
AUX_SOURCE_DIRECTORY(filters FILTER_SRC)
AUX_SOURCE_DIRECTORY(plugins PLUGIN_SRC)
AUX_SOURCE_DIRECTORY(models MODEL_SRC)

include_directories(/usr/local/include)
include_directories(/usr/include)

FILE(GLOB SCP_LIST ${CMAKE_CURRENT_SOURCE_DIR}/views/*.csp)
foreach(cspFile ${SCP_LIST})
    message(STATUS "cspFile:" ${cspFile})
    EXEC_PROGRAM(basename ARGS "${cspFile} .csp" OUTPUT_VARIABLE classname)
    message(STATUS "view classname:" ${classname})
    add_custom_command(OUTPUT ${classname}.h ${classname}.cc
            COMMAND drogon_ctl
            ARGS create view ${cspFile}
            DEPENDS ${cspFile}
            VERBATIM )
    set(VIEWSRC ${VIEWSRC} ${classname}.cc)
endforeach()

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_subdirectory(core)
#add_subdirectory(test)
#include_directories("$ENV{HOME}/k/jewelApp/src")
#find_library(CONN_LIB libjewelconnection HINT "$ENV{HOME}/k/build-jewelApp-Desktop_Qt_5_13_0_GCC_64bit-Debug/src/core/connection")
#find_library(CORE_LIB libjewelcore2 HINT "$ENV{HOME}/k/build-jewelApp-Desktop_Qt_5_13_0_GCC_64bit-Debug/src/core")
add_executable(jdragon ${SRC_DIR} ${WSCTL_SRC} ${WSCTL_SRC_CONTEXT} ${HTTPCTL_SRC} ${ACTOR_SRC} ${FILTER_SRC} ${VIEWSRC} ${PLUGIN_SRC} ${MODEL_SRC})

target_link_libraries(jdragon
  # ${CONN_LIB}
  # ${CORE_LIB}
  libjewelcore2
  Threads::Threads
  ${CMAKE_DL_LIBS}
  ${_OPTIONAL_LIBS}
  # ${UUID_LIBRARY}
  ZLIB::ZLIB
  PostgreSQL::PostgreSQL
  ${DROGON_LIBRARIES}
  ${CAF_LIBRARIES}
  Boost::filesystem
  fmt::fmt
  # absl::strings
  # clang_flags
  # Boost::timer
  # Poco::Foundation
  # Boost::disable_autolinking
  # Boost::filesystem
  # angelscript
  # TBB::tbb
  # easyloggingpp
  #Wt::Wt Wt::Dbo Wt::FCGI Wt::HTTP
)
