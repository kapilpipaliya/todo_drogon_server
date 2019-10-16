cmake_minimum_required (VERSION 3.15)

## This includes the Vita toolchain, must go before project definition
# It is a convenience so you do not have to type
# -DCMAKE_TOOLCHAIN_FILE=$VITASDK/share/vita.toolchain.cmake for cmake. It is
# highly recommended that you include this block for all projects.

if(NOT DEFINED CMAKE_TOOLCHAIN_FILE)
  if(DEFINED ENV{HOME})
    set(CMAKE_TOOLCHAIN_FILE "$ENV{HOME}/k/cpp_stuff/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE PATH "toolchain file")
  else()
    message(FATAL_ERROR "$ENV{HOME}/k/cpp_stuff/vcpkg/scripts/buildsystems/vcpkg.cmake vcpkg path wrong!")
  endif()
endif()


#find_program(IWYU_PATH NAMES include-what-you-use iwyu)
#if(NOT IWYU_PATH)
#  message(FATAL_ERROR "Could not find the program include-what-you-use")
#endif()
#set(CMAKE_CXX_INCLUDE_WHAT_YOU_USE ${IWYU_PATH})
#set(CMAKE_C_INCLUDE_WHAT_YOU_USE ${IWYU_PATH})

Project(jdragon)

include_directories("$ENV{HOME}/k/cpp_stuff/vcpkg/installed/x64-linux/include")

set(CMAKE_CXX_STANDARD 20)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

include(CheckIncludeFileCXX)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

#faster compile https://www.bitsnbites.eu/faster-c-builds/
if (UNIX AND NOT APPLE)
  execute_process(COMMAND ${CMAKE_C_COMPILER} -fuse-ld=gold -Wl,--version ERROR_QUIET OUTPUT_VARIABLE ld_version)
  if ("${ld_version}" MATCHES "GNU gold")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fuse-ld=gold -Wl,--disable-new-dtags")
    set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -fuse-ld=gold -Wl,--disable-new-dtags")
  endif()
endif()

#find_package(Drogon CONFIG REQUIRED)
#include_directories(${DROGON_INCLUDE_DIRS})
#link_libraries(${DROGON_LIBRARIES})
add_subdirectory(thirdparty/drogon)

set(THREADS_PREFER_PTHREAD_FLAG TRUE)
find_package(Threads REQUIRED)
find_package(protobuf CONFIG REQUIRED)

remove_definitions(USE_MYSQL)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -Wall ${CMAKE_CXX_STD_FLAGS}")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Wall ${CMAKE_CXX_STD_FLAGS}")

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake_modules/ "$ENV{HOME}/k/cpp_stuff/actor-framework/cmake/")

#find_package (UUID REQUIRED)

find_package (OpenSSL)
if(OpenSSL_FOUND)
    list(APPEND _OPTIONAL_LIBS OpenSSL::SSL OpenSSL::Crypto)
endif()

find_package(ZLIB REQUIRED)

find_package(PostgreSQL REQUIRED)

#find_package(Boost REQUIRED COMPONENTS chrono filesystem date_time program_options iostreams)
set(BOOST_ROOT "$ENV{HOME}/k/cpp_stuff/vcpkg/installed/x64-linux")
find_package(Boost REQUIRED COMPONENTS filesystem locale) #1.71.0
set (Boost_ARCHITECTURE "-x64")
# find_package(Boost REQUIRED COMPONENTS filesystem date_time system timer)
#find_package(cppzmq REQUIRED)
find_package(PNG REQUIRED)
find_package(Threads REQUIRED)
find_package(OpenSSL REQUIRED)
#find_package(GDAL REQUIRED)
#find_package(msgpack REQUIRED)
find_package(fmt REQUIRED)
find_package(yaml-cpp CONFIG REQUIRED)

find_package(jsoncpp CONFIG REQUIRED)
#target_link_libraries(main PRIVATE jsoncpp_lib)
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
 find_package(amqpcpp CONFIG REQUIRED)
 find_package(Angelscript CONFIG REQUIRED)
# include_directories(/home/kapili3/k/cpp_stuff/vcpkg/installed/x64-linux/include)
  find_package(units CONFIG REQUIRED)
  find_package(msgpack CONFIG REQUIRED)
   find_package(kangaru CONFIG REQUIRED)
   set(CMAKE_AUTOMOC ON)
   set(CMAKE_AUTORCC ON)
   SET(CMAKE_AUTOUIC ON)
find_package(Qt5 COMPONENTS Core Gui Widgets Network Xml Sql REQUIRED)
find_package(msgpack CONFIG REQUIRED)
find_package(pegtl CONFIG REQUIRED)
find_package(range-v3 CONFIG REQUIRED)
find_package(gRPC CONFIG REQUIRED)
# https://gist.github.com/Asher-/617872
#	function processes each sub-directory and then adds each source file in directory
#	each function should cascade back upward in setting variables so that the bottom directory
#	adds its source first, and then the level above it adds its source and passes both up, and so on...
function( recursively_include_src which_directory return_variable )

  if( ${return_variable} STREQUAL "headers" )
    set( file_extension ".h" )
  else( ${return_variable} STREQUAL "headers" )
    set( file_extension ".c" )
  endif( ${return_variable} STREQUAL "headers" )

  #	get list of all files for this directory
  file( GLOB this_directory_all_files "${which_directory}/*" )

  #	get list of source from this directory
  file( GLOB this_directory_src "${which_directory}/*${file_extension}" )

  #	get rid of *.txt
  file( GLOB this_directory_txt "${which_directory}/*.txt" )

  #	get directories only
  if( this_directory_all_files AND this_directory_txt )
    #	remove txt from list of files to get list of directories
    list( REMOVE_ITEM this_directory_all_files ${this_directory_txt} )
  endif( this_directory_all_files AND this_directory_txt )
  if( this_directory_all_files AND this_directory_src )
    #	remove source from list of files to get list of directories
    list( REMOVE_ITEM this_directory_all_files ${this_directory_src} )
    set( this_directory_directories ${this_directory_all_files} )
    #	for each sub-directory, call self with sub-directory as arg
    foreach( this_sub_directory ${this_directory_directories} )
      recursively_include_src( ${this_sub_directory} ${return_variable} )
    endforeach( this_sub_directory ${this_directory_directories} )
  endif( this_directory_all_files AND this_directory_src )

  #	add source files to ${rb_rpdb_src} in PARENT_SCOPE
  if( ${return_variable} STREQUAL "headers" )
    set( rb_rpdb_headers ${rb_rpdb_headers} ${this_directory_src} PARENT_SCOPE )
  else( ${return_variable} STREQUAL "headers" )
    set( rb_rpdb_src ${rb_rpdb_src} ${this_directory_src} PARENT_SCOPE )
  endif( ${return_variable} STREQUAL "headers" )

  set( rb_rpdb_directories ${rb_rpdb_directories} ${which_directory} PARENT_SCOPE )

endfunction( recursively_include_src which_directory return_variable )



AUX_SOURCE_DIRECTORY(./ SRC_DIR)
AUX_SOURCE_DIRECTORY(wscontroller WSCTL_SRC)
AUX_SOURCE_DIRECTORY(wscontroller/context WSCTL_SRC_CONTEXT)
AUX_SOURCE_DIRECTORY(httpcontroller HTTPCTL_SRC)
AUX_SOURCE_DIRECTORY(actor ACTOR_SRC)
AUX_SOURCE_DIRECTORY(filters FILTER_SRC)
AUX_SOURCE_DIRECTORY(plugins PLUGIN_SRC)
AUX_SOURCE_DIRECTORY(models MODEL_SRC)
AUX_SOURCE_DIRECTORY(gui MODEL_SRC)
AUX_SOURCE_DIRECTORY(gui/widgets/script MODEL_SRC)
AUX_SOURCE_DIRECTORY(gui/widgets/script/editor MODEL_SRC)
AUX_SOURCE_DIRECTORY(gui/widgets MODEL_SRC)
AUX_SOURCE_DIRECTORY(gui/widgets/dgraphlog MODEL_SRC)
AUX_SOURCE_DIRECTORY(gui/MdiMainWindow MODEL_SRC)
set(QRC1_DIR ./gui/widgets/script/editor/application.qrc)
#recursively_include_src(thirdparty/angelscriptaddons ANGLE_SCRIPT_ADDONS_SRC)
AUX_SOURCE_DIRECTORY(thirdparty/angelscriptaddons/autowrapper ANGLE_SCRIPT_ADDONS_SRC1)
AUX_SOURCE_DIRECTORY(thirdparty/angelscriptaddons/contextmgr ANGLE_SCRIPT_ADDONS_SRC2)
AUX_SOURCE_DIRECTORY(thirdparty/angelscriptaddons/datetime ANGLE_SCRIPT_ADDONS_SRC3)
AUX_SOURCE_DIRECTORY(thirdparty/angelscriptaddons/debugger ANGLE_SCRIPT_ADDONS_SRC4)
AUX_SOURCE_DIRECTORY(thirdparty/angelscriptaddons/scriptany ANGLE_SCRIPT_ADDONS_SRC5)
AUX_SOURCE_DIRECTORY(thirdparty/angelscriptaddons/scriptarray ANGLE_SCRIPT_ADDONS_SRC6)
AUX_SOURCE_DIRECTORY(thirdparty/angelscriptaddons/scriptbuilder ANGLE_SCRIPT_ADDONS_SRC7)
AUX_SOURCE_DIRECTORY(thirdparty/angelscriptaddons/scriptdictionary ANGLE_SCRIPT_ADDONS_SRC8)
AUX_SOURCE_DIRECTORY(thirdparty/angelscriptaddons/scriptfile ANGLE_SCRIPT_ADDONS_SRC9)
AUX_SOURCE_DIRECTORY(thirdparty/angelscriptaddons/scriptgrid ANGLE_SCRIPT_ADDONS_SRC10)
AUX_SOURCE_DIRECTORY(thirdparty/angelscriptaddons/scripthandle ANGLE_SCRIPT_ADDONS_SRC11)
AUX_SOURCE_DIRECTORY(thirdparty/angelscriptaddons/scripthelper ANGLE_SCRIPT_ADDONS_SRC12)
AUX_SOURCE_DIRECTORY(thirdparty/angelscriptaddons/scriptmath ANGLE_SCRIPT_ADDONS_SRC13)
AUX_SOURCE_DIRECTORY(thirdparty/angelscriptaddons/scriptstdstring ANGLE_SCRIPT_ADDONS_SRC14)
AUX_SOURCE_DIRECTORY(thirdparty/angelscriptaddons/serializer ANGLE_SCRIPT_ADDONS_SRC15)
AUX_SOURCE_DIRECTORY(thirdparty/angelscriptaddons/weakref ANGLE_SCRIPT_ADDONS_SRC16)
AUX_SOURCE_DIRECTORY(anglescript MODEL_SRC)
include_directories(thirdparty/)
aux_source_directory(thirdparty/pystring MODEL_SRC)

include_directories(/usr/local/include)
include_directories(/usr/include)
include_directories(/core/service/time)


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
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/actor)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/actor/inc)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/wscontroller)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/thirdparty)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/gui)

add_subdirectory(core)
#add_subdirectory(test)
#include_directories("$ENV{HOME}/k/jewelApp/src")
#find_library(CONN_LIB libjewelconnection HINT "$ENV{HOME}/k/build-jewelApp-Desktop_Qt_5_13_0_GCC_64bit-Debug/src/core/connection")
#find_library(CORE_LIB libjewelcore2 HINT "$ENV{HOME}/k/build-jewelApp-Desktop_Qt_5_13_0_GCC_64bit-Debug/src/core")
add_executable(jdragon ${SRC_DIR} ${WSCTL_SRC} ${WSCTL_SRC_CONTEXT} ${HTTPCTL_SRC} ${ACTOR_SRC} ${FILTER_SRC} ${VIEWSRC} ${PLUGIN_SRC} ${MODEL_SRC}
    ${ANGLE_SCRIPT_ADDONS_SRC1}
    ${ANGLE_SCRIPT_ADDONS_SRC2}
    ${ANGLE_SCRIPT_ADDONS_SRC3}
    ${ANGLE_SCRIPT_ADDONS_SRC4}
    ${ANGLE_SCRIPT_ADDONS_SRC5}
    ${ANGLE_SCRIPT_ADDONS_SRC6}
    ${ANGLE_SCRIPT_ADDONS_SRC7}
    ${ANGLE_SCRIPT_ADDONS_SRC8}
    ${ANGLE_SCRIPT_ADDONS_SRC9}
    ${ANGLE_SCRIPT_ADDONS_SRC10}
    ${ANGLE_SCRIPT_ADDONS_SRC11}
    ${ANGLE_SCRIPT_ADDONS_SRC12}
    ${ANGLE_SCRIPT_ADDONS_SRC13}
    ${ANGLE_SCRIPT_ADDONS_SRC14}
    ${ANGLE_SCRIPT_ADDONS_SRC15}
    ${ANGLE_SCRIPT_ADDONS_SRC16}
    ${QRC1_DIR}
    )

target_link_libraries(jdragon
  # ${CONN_LIB}
  # ${CORE_LIB}

  Threads::Threads
  ${CMAKE_DL_LIBS}
  ${_OPTIONAL_LIBS}
  # ${UUID_LIBRARY}
  ZLIB::ZLIB
#  ${DROGON_LIBRARIES}
  drogon
  ${CAF_LIBRARIES}
  Boost::filesystem
  fmt::fmt
  Boost::locale
  jsoncpp_lib
  yaml-cpp
  # absl::strings
  # clang_flags
  # Boost::timer
  # Poco::Foundation
  # Boost::disable_autolinking
  # angelscript
  # TBB::tbb
  # easyloggingpp
  #Wt::Wt Wt::Dbo Wt::FCGI Wt::HTTP
#  amqpcpp
  # units
  Angelscript::angelscript
  kangaru
  Qt5::Core
  Qt5::Gui
  Qt5::Widgets
  Qt5::Network
  Qt5::Xml
  Qt5::Sql
  # https://github.com/microsoft/vcpkg/issues/7205
#  msgpackc
#  msgpackc-cxx
#  msgpackc-static
  taocpp::pegtl
  protobuf::libprotoc protobuf::libprotobuf protobuf::libprotobuf-lite
  range-v3
  gRPC::gpr gRPC::grpc gRPC::grpc++
  dgraph
  libjewelcore2
  time
)
#generate drpc for cpp:
#pb --plugin=protoc-gen-grpc=/home/kapili3/k/cpp_stuff/vcpkg/installed/x64-linux/tools/grpc/grpc_cpp_plugin --grpc_out=./generated/ --proto_path=./protos/ api.proto
#pb --cpp_out=./generated/ --proto_path=./protos/ api.proto

#target_link_libraries(greeter_client PRIVATE c-ares::cares protobuf::libprotoc protobuf::libprotobuf protobuf::libprotobuf-lite gRPC::gpr gRPC::grpc++ -pthread)
add_subdirectory(core/dgraph/ormtest)
add_subdirectory(core/service/time)
