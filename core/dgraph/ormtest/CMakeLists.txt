cmake_minimum_required(VERSION 3.15.1)


set(HDR

)

set(SRC
  main.cpp
)

include_directories(..)
aux_source_directory(. SRC)
aux_source_directory(../../../thirdparty/pystring SRC)
add_executable(ormtest
    ${HDR}
    ${SRC}
)

target_link_libraries(ormtest
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
