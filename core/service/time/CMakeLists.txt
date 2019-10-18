cmake_minimum_required(VERSION 3.15.1)

#set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake_modules/)
set(CMAKE_CXX_STANDARD 20)

set(HDR

)

set(SRC

)

include_directories(..)

AUX_SOURCE_DIRECTORY(. SRC)
AUX_SOURCE_DIRECTORY(./auth/ SRC)
AUX_SOURCE_DIRECTORY(./auth/user/ SRC)
AUX_SOURCE_DIRECTORY(./auth/user/registration SRC)
AUX_SOURCE_DIRECTORY(./auth/user/registration/proto SRC)
AUX_SOURCE_DIRECTORY(./auth/user/login SRC)
AUX_SOURCE_DIRECTORY(./auth/user/login/proto SRC)
AUX_SOURCE_DIRECTORY(./auth/user/logout SRC)
AUX_SOURCE_DIRECTORY(./auth/user/logout/proto SRC)
AUX_SOURCE_DIRECTORY(./menu SRC)

aux_source_directory(. SRC)
aux_source_directory(../../../thirdparty/pystring SRC)
add_library(time
    SHARED
    ${HDR}
    ${SRC}
)

target_link_libraries(time
    PRIVATE
    dgraph

    Boost::filesystem
    fmt::fmt
    protobuf::libprotoc protobuf::libprotobuf protobuf::libprotobuf-lite
    range-v3
    gRPC::gpr gRPC::grpc gRPC::grpc++
#    folly.a
#    folly
)
