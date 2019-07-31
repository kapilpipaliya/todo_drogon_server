cmake_minimum_required(VERSION 3.14.1)
project(libjewelcore2)
#set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake_modules/)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
SET(CMAKE_AUTOUIC ON)

find_package(Qt5 COMPONENTS Core Gui REQUIRED)

find_package(PostgreSQL)
find_package(libpqxx REQUIRED)

find_package (Jsoncpp REQUIRED)
#find_package(Sqlpp11)
#find_package(Sqlpp-connector-postgresql)
#find_package(folly)

set(JEWEL_HDR


    tables/Table.h
    tables/condformat.h
    tables/data.h
    tables/macro.h

    tables/query/accountquery.h
    tables/query/entityquery.h
    tables/query/materialquery.h
    tables/query/menuquery.h
    tables/query/mfgquery.h
    tables/query/productquery.h
    tables/query/settingquery.h
    tables/query/postquery.h


###    sql/sqlitetypes.h # this file is good and it is in the directory
    sql/query.h
    sql/objectidentifier.h
#    csvparser.h
#    sqlitedb.h not needed use mdb.h
    settings.h
    dotenvformat.h
    ciphersettings.h

    json.hpp
    modelenums.h
    tables/jsonfns.h


    tables/savedel/accountsave.h
    tables/savedel/entitysave.h
    tables/savedel/materialsave.h
    tables/savedel/menusave.h
    tables/savedel/mfgsave.h
    tables/savedel/productsave.h
    tables/savedel/settingsave.h
    tables/savedel/postsave.h

    strfns.h
)

set(JEWEL_SRC


    tables/Table.cpp
    tables/condformat.cpp
    tables/data.cpp

###    sql/sqlitetypes.cpp
    sql/query.cpp
    sql/objectidentifier.cpp
#    sqltextedit.cpp
#    sqlitedb.cpp not needed ufse mdb.cpp
    settings.cpp
    dotenvformat.cpp
    ciphersettings.cpp

    tables/jsonfns.cpp

    tables/query/accountquery.cpp
    tables/query/entityquery.cpp
    tables/query/materialquery.cpp
    tables/query/menuquery.cpp
    tables/query/mfgquery.cpp
    tables/query/productquery.cpp
    tables/query/settingquery.cpp
    tables/query/postquery.cpp

    tables/savedel/accountsave.cpp
    tables/savedel/entitysave.cpp
    tables/savedel/materialsave.cpp
    tables/savedel/menusave.cpp
    tables/savedel/mfgsave.cpp
    tables/savedel/productsave.cpp
    tables/savedel/settingsave.cpp
    tables/savedel/postsave.cpp

    strfns.cpp
)

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
    Qt5::Core
    Qt5::Gui
    PostgreSQL::PostgreSQL
    libpqxx::pqxx_shared
    libjewelconnection
    ${JSONCPP_LIBRARY}
#    folly.a
#    folly
)
add_subdirectory(connection)
