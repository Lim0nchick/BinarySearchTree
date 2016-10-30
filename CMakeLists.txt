cmake_minimum_required(VERSION 3.5.1)
project(BinarySearchTree)

cmake_minimum_required(VERSION 3.6)
project(BinarySearchTree_master)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        examples/main.cpp
        include/BinarySearchTree.hpp
        source/BinarySearchTree.cpp
        tests/catch.hpp
        tests/find.cpp
        tests/insert.cpp
        tests/main.cpp
        tests/remove.cpp
        tests/size.cpp
        appveyor.yml
        CMakeLists.txt
        README.md)

add_executable(BinarySearchTree ${SOURCE_FILES})