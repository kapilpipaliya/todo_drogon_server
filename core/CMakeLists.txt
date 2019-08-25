cmake_minimum_required(VERSION 3.15.1)
project(libjewelcore2)
#set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake_modules/)

find_package(PostgreSQL)
#find_package(libpqxx REQUIRED)

#find_package (Jsoncpp REQUIRED)
#find_package(Sqlpp11)
#find_package(Sqlpp-connector-postgresql)
#find_package(folly)

set(JEWEL_HDR
    sql/Table.h
    sql/condformat.h
#    data.h

###    sql/sqlitetypes.h # this file is good and it is in the directory
    sql/query.h
    sql/objectidentifier.h
    actor/permission.h
    actor/validation.h
#    csvparser.h
#    sqlitedb.h not needed use mdb.h
#    settings.h
#    dotenvformat.h
#    ciphersettings.h

    jsonfns.h

    strfns.h
)

set(JEWEL_SRC
    sql/Table.cpp
    sql/condformat.cpp
#    data.cpp
actor/permission.cpp
actor/validation.cpp

###    sql/sqlitetypes.cpp
    sql/query.cpp
    sql/objectidentifier.cpp
#    sqltextedit.cpp
#    sqlitedb.cpp not needed ufse mdb.cpp
#    settings.cpp
#    dotenvformat.cpp
#    ciphersettings.cpp

    jsonfns.cpp

    strfns.cpp
)
AUX_SOURCE_DIRECTORY(./service/jadmin JEWEL_SRC)
AUX_SOURCE_DIRECTORY(./service/jadmin/auth JEWEL_SRC)
AUX_SOURCE_DIRECTORY(./service/jadmin/post JEWEL_SRC)
AUX_SOURCE_DIRECTORY(./service/jadmin/account JEWEL_SRC)
AUX_SOURCE_DIRECTORY(./service/jadmin/entity JEWEL_SRC)
AUX_SOURCE_DIRECTORY(./service/jadmin/material JEWEL_SRC)
AUX_SOURCE_DIRECTORY(./service/jadmin/menu JEWEL_SRC)
AUX_SOURCE_DIRECTORY(./service/jadmin/mfg JEWEL_SRC)
AUX_SOURCE_DIRECTORY(./service/jadmin/product JEWEL_SRC)
AUX_SOURCE_DIRECTORY(./service/jadmin/setting JEWEL_SRC)

AUX_SOURCE_DIRECTORY(./service/juser JEWEL_SRC)

AUX_SOURCE_DIRECTORY(./service/madmin JEWEL_SRC)

AUX_SOURCE_DIRECTORY(./service/muser JEWEL_SRC)

#set(JEWEL_RESOURCES
#    languages.qrc
#)
include_directories(..)

add_library(${PROJECT_NAME}
    SHARED
    ${JEWEL_HDR}
    ${JEWEL_SRC}
#    ${JEWEL_RESOURCES}
)
#install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX})#OR
#install(TARGETS ${PROJECT_NAME} LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
install(TARGETS ${PROJECT_NAME} LIBRARY DESTINATION /home/kapili3)

#set_target_properties(${PROJECT_NAME} PROPERTIES PREFIX "")

target_link_libraries(${PROJECT_NAME}
    PRIVATE
    PostgreSQL::PostgreSQL
#    libpqxx::pqxx_shared
#    libjewelconnection
#    ${JSONCPP_LIBRARY}
#    folly.a
#    folly
)

#add_subdirectory(connection)
