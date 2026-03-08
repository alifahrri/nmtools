set(CMAKE_C_COMPILER gcc-9)
set(CMAKE_CXX_COMPILER g++-9)

# ignore strict-aliasing warning in gcc9
add_compile_options(-W -Wall -Werror -Wextra -Wno-error=unknown-pragmas -Wno-error=bool-compare -wno-error=strict-aliasing)