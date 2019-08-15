cmake_minimum_required (VERSION 3.15)
Project(jdragon)

set(CMAKE_CXX_STANDARD 20)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

set(THREADS_PREFER_PTHREAD_FLAG TRUE)
find_package(Threads REQUIRED)

remove_definitions(USE_MYSQL)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall ${CMAKE_CXX_STD_FLAGS}")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall ${CMAKE_CXX_STD_FLAGS}")

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake_modules/)
find_package(Boost REQUIRED COMPONENTS filesystem date_time system timer )

#include_directories(/usr/local/include/Urho3D/include /usr/local/include/Urho3D/ThirdParty)

#jsoncpp
find_package (Jsoncpp REQUIRED)
#include_directories(${JSONCPP_INCLUDE_DIRS})
#link_libraries(${JSONCPP_LIBRARIES})

#uuid
find_package (UUID REQUIRED)
#include_directories(${UUID_INCLUDE_DIR})
#link_libraries(${UUID_LIBRARIES})

#OpenSSL
find_package (OpenSSL)
if(OpenSSL_FOUND)
    list(APPEND _OPTIONAL_LIBS OpenSSL::SSL OpenSSL::Crypto)
endif()

#zlib
find_package(ZLIB REQUIRED)

#find postgres
find_package(PostgreSQL REQUIRED)
find_package(libpqxx REQUIRED)


#Find sqlite3.
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
#find_package(TBB REQUIRED)
#find_package(Angelscript REQUIRED)
#find_package(easyloggingpp REQUIRED)
find_package(RapidJSON REQUIRED)

#find_package(CAF REQUIRED)
#find_package(HighFive 2.0 REQUIRED)
#https://abseil.io/docs/cpp/quickstart-cmake
#git clone https://github.com/abseil/abseil-cpp.git
# Process Abseil's CMake build system
#add_subdirectory(abseil-cpp)


AUX_SOURCE_DIRECTORY(./ SRC_DIR)
AUX_SOURCE_DIRECTORY(controllers CTL_SRC)
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
add_subdirectory(test)
#include_directories("/home/kapili3/k/jewelApp/src")
#find_library(CONN_LIB libjewelconnection HINT /home/kapili3/k/build-jewelApp-Desktop_Qt_5_13_0_GCC_64bit-Debug/src/core/connection)
#find_library(CORE_LIB libjewelcore2 HINT /home/kapili3/k/build-jewelApp-Desktop_Qt_5_13_0_GCC_64bit-Debug/src/core)
add_executable(jdragon ${SRC_DIR} ${CTL_SRC} ${FILTER_SRC} ${VIEWSRC} ${PLUGIN_SRC} ${MODEL_SRC})

  #  libpqxx::pqxx_shared
target_link_libraries(jdragon
  Threads::Threads

#/usr/local/lib64/Urho3D/libUrho3D.a
  ${CMAKE_DL_LIBS}
  ${_OPTIONAL_LIBS}
  ${JSONCPP_LIBRARY}
  ${UUID_LIBRARY}
  ZLIB::ZLIB
  #${CONN_LIB}
  #${CORE_LIB}
  PostgreSQL::PostgreSQL
  libpqxx::pqxx_shared
  libjewelconnection
  libjewelcore2
  drogon
  trantor
  Boost::filesystem

#  absl::strings


# clang_flags
# Boost::timer
#Poco::Foundation
# Boost::disable_autolinking
# Boost::filesystem
fmt::fmt
libpqxx::pqxx_shared
#angelscript
#TBB::tbb
#easyloggingpp
#rapidjson

)
