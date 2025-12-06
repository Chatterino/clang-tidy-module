cmake_minimum_required(VERSION 3.15..4.0)

project(chatterino-clang-tidy-module
    VERSION 0.1.0
    DESCRIPTION "clang-tidy module with checks specialized for Chatterino"
    HOMEPAGE_URL "https://chatterino.com/"
    )

find_package(LLVM REQUIRED CONFIG)
find_package(Clang REQUIRED CONFIG)

message(STATUS "Using LLVM from ${LLVM_DIR}")
message(STATUS "Using Clang from ${Clang_DIR}")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(src)
if (BUILD_TESTING)
    add_subdirectory(tests)
endif()
