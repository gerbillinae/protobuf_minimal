cmake_minimum_required(VERSION 3.29)
project(protobuf_minimal)
set(CMAKE_CXX_STANDARD 17)

# This lets us build protoc from the project root and gives us the cmake target protobuf::libprotobuf
add_subdirectory(thirdparty)

add_executable(main)

# Get all the generated protobuf files
file(GLOB PROTO_FILES ./generated/*.pb.cc)

target_sources(main PRIVATE main.cpp ${PROTO_FILES})

target_link_libraries(main protobuf::libprotobuf)