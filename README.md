# Minimal protobuffers in C++

This may be the most straight-forward way of using protobuffers in a c++ project.

The file `main.cpp` demonstrates creating, serializing and deserializing protobuf objects.

This guide is aimed at Linux.
While it should work on Mac, as of writing (August 2024) there is a linking issue in protobuf's abseil dependency when building with `clang` on arm64.

Mac users should use a linux VM (e.g. Orbstack). Windows users may prefer using WSL2.

## Get the Protobuf submodule

Clone the repository using:
```bash
git clone --recurse-submodules <repository-url>
```
If you have already cloned the repository without the `--recursive-submodules` flag, run:
```bash
git submodule update --init --recursive 
```

## Build `protoc`

```bash
mkdir cmake-build-debug
cd cmake-build-debug
cmake ..
cmake --build . --target protoc
```
Building the `protoc` target puts the 

## Use `protoc` to generate c++ files from our `.proto` file

Return to the project root with `cd ..` and run:
```bash
./cmake-build-debug/thirdparty/protobuf/protoc \
  --cpp_out=./generated \
  --proto_path=. \
  ./*.proto
```

## Build and Run `main`
The `main` target is defined in the root `./CMakeLists.txt`. This is our code.
```bash
cd cmake-build-debug
cmake ..
cmake --build . --target main
```
Do not forget the `cmake ..` command, otherwise the `*.pb.cc` and `*.pb.h` files will not be part of your build tree! 

You should now be able to run the `main` executable in the `cmake-build-debug` directory.
```bash
./main
```
```text
Testing Person Serialization
Name: John
ID: 123
Email: john@example.com
Phone: 555-4321 (2)

Testing AddressBook Serialization
Name: Bob
ID: 1
Email: bob@example.com
Phone: 555-4321 (2)
Name: Alice
ID: 2
Email: alice@example.com
Phone: 324-3353 (1)
Phone: 342-3588 (3)
```

## Conclusion

The advantages of this approach include:
1. Using the protoc built from the same repository that we will link against ensures `GOOGLE_PROTOBUF_VERIFY_VERSION` will succeed.

This downsides of this approach include:
1. Generated protobuf files are put into the source tree, rather than the build tree.
2. Protobuf files are generated outside of cmake. If the `.proto` files change, `protoc` needs to be run again.

The followup [grpc_with_vcpkg](https://github.com/gerbillinae/grpc_with_vcpkg) gets around these downsides.
