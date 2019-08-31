cmake_minimum_required(VERSION 3.15.1)
project(libwsclient)
#set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake_modules/)

#find_package(folly)

find_package(Qt5 COMPONENTS Core Gui Network Xml Sql WebSockets REQUIRED)

set(HDR

)

set(SRC

)
AUX_SOURCE_DIRECTORY(./ SRC)

include_directories(..)

add_library(${PROJECT_NAME}
    SHARED
    ${HDR}
    ${SRC}
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
    Qt5::Core
    Qt5::Gui
    Qt5::Network
    Qt5::WebSockets
)

#add_subdirectory(connection)
