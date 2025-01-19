set(CMAKE_C_COMPILER clang-10)
set(CMAKE_CXX_COMPILER clang++-10)

add_compile_options(-W -Wall -Werror -Wextra -Wno-gnu-string-literal-operator-template -Wno-deprecated-declarations)