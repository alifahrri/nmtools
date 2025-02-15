set(CMAKE_C_COMPILER hipcc)
set(CMAKE_CXX_COMPILER hipcc)

add_compile_options(-W -Wall -Wextra -Werror
    -Wno-gnu-string-literal-operator-template
)