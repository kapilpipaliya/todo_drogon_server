cmake_minimum_required(VERSION 3.15.1)

AUX_SOURCE_DIRECTORY(./ SRC)
AUX_SOURCE_DIRECTORY(./dgraph-js/generated SRC)
AUX_SOURCE_DIRECTORY(./dgraphgrpc SRC)
AUX_SOURCE_DIRECTORY(./dgraphhttp SRC)
AUX_SOURCE_DIRECTORY(./dgraphhttp/httpendpoint SRC)
AUX_SOURCE_DIRECTORY(./orm SRC)

include_directories(..)
aux_source_directory(../thirdparty/pystring SRC)
add_library(dgraph SHARED
    ${HDR}
    ${SRC}
)


target_link_libraries(dgraph
    PRIVATE

    Boost::filesystem
    fmt::fmt
    protobuf::libprotoc protobuf::libprotobuf protobuf::libprotobuf-lite
    range-v3
     gRPC::gpr gRPC::grpc gRPC::grpc++
#    folly.a
#    folly
)
