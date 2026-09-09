find_file(llvm_lit_py_path 
    NAMES lit.py llvm-lit llvm-lit.py
    HINTS "${LLVM_INSTALL_PREFIX}/build/utils/lit"
    REQUIRED
)

message(STATUS "Using LLVM binary dir at ${LLVM_TOOLS_BINARY_DIR}")
configure_file(lit.site.cfg.py.in lit.site.cfg.py @ONLY)

add_custom_target(check-chatterino-clang-tidy-module
  COMMAND "${llvm_lit_py_path}" "${CMAKE_CURRENT_BINARY_DIR}" -v
  DEPENDS chatterino-clang-tidy-module)

add_dependencies(check-chatterino-clang-tidy-module chatterino-clang-tidy-module)
