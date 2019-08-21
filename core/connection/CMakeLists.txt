cmake_minimum_required(VERSION 3.15.2)
project(libjewelconnection)

find_package(PostgreSQL)

# very good cmakelist file that include many libraries also pqxx example in it:
#https://github.com/suryakiran/cmake-test/blob/master/CMakeLists.txt

# find_package(Boost REQUIRED COMPONENTS chrono filesystem date_time program_options iostreams)
#set (Boost_ARCHITECTURE "-x64")
# find_package(Boost REQUIRED COMPONENTS filesystem date_time system timer)
#find_package(cppzmq REQUIRED)
#find_package(PNG REQUIRED)
#find_package(Threads REQUIRED)
#find_package(OpenSSL REQUIRED)
#find_package(aws-cpp-sdk-core)
#find_package(aws-cpp-sdk-s3)
#find_package(GDAL REQUIRED)
#find_package(msgpack REQUIRED)
#find_package(fmt REQUIRED)
#find_package(PostgreSQL REQUIRED)
#find_package(Qt5Widgets REQUIRED)
#find_package(Poco REQUIRED COMPONENTS Foundation JSON Util XML Zip)
#find_package(TBB REQUIRED)
#find_package(Angelscript REQUIRED)
#find_package(libpqxx REQUIRED)
#find_package(easyloggingpp REQUIRED)
#find_package(RapidJSON REQUIRED)

set(JEWEL_HDR
    mdb.h
    pdb.h

)

set(JEWEL_SRC
    mdb.cpp
    pdb.cpp
)

add_library(${PROJECT_NAME}
    SHARED
    ${JEWEL_HDR}
    ${JEWEL_SRC}
)


target_link_libraries(${PROJECT_NAME}
    PRIVATE
    PostgreSQL::PostgreSQL
    libpqxx::pqxx_shared
)
#install(TARGETS ${PROJECT_NAME} LIBRARY DESTINATION ${MODULES_INSTALL_PATH})
install(TARGETS ${PROJECT_NAME} LIBRARY DESTINATION /home/kapili3)

#target_link_libraries(test PUBLIC
  # clang_flags
  # Boost::timer
#  Poco::Foundation
  # Boost::disable_autolinking
  # Boost::filesystem
#  fmt::fmt
#  libpqxx::pqxx_shared
#  PostgreSQL::PostgreSQL
#  angelscript
#  TBB::tbb
#  easyloggingpp
#  rapidjson
#  )
