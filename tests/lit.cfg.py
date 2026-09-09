import lit.formats
import sys
import os

match sys.platform:
    case "linux":
        shlibext = ".so"
    case "darwin":
        shlibext = ".dylib"
    case "win32":
        shlibext = ".dll"
    case _:
        raise NotImplementedError()


config.name = "Chatterino clang-tidy-module"
config.test_format = lit.formats.ShTest(True)

config.suffixes = [".cpp", ".test"]

config.test_source_root = os.path.dirname(__file__)
config.test_exec_root = os.path.join(config.c2_obj_root, "test")

c2_module = os.path.join(
    config.c2_obj_root, "src", f"chatterino-clang-tidy-module{shlibext}"
)
config.substitutions.append(("%c2-module", c2_module))
config.substitutions.append(
    ("%c2-clang-tidy", f"clang-tidy -load={c2_module} --checks='chatterino-*'")
)

config.environment["PATH"] = os.path.pathsep.join(
    (config.llvm_tools_binary_dir, config.environment.get("PATH", ""))
)
