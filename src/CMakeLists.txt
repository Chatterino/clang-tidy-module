add_library(chatterino-clang-tidy-module SHARED
    module.cpp

    checks/explicit-this.hpp
    checks/explicit-this.cpp
)

target_include_directories(chatterino-clang-tidy-module PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}

    ${LLVM_INCLUDE_DIRS}
    ${CLANG_INCLUDE_DIRS}
)
