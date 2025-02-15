set(CMAKE_C_COMPILER /usr/local/bin/acpp)
set(CMAKE_CXX_COMPILER /usr/local/bin/acpp)

SET (CMAKE_C_COMPILER_WORKS 1)
add_compile_options(-W -Wall -Werror -Wextra -Wno-gnu-string-literal-operator-template -fopenmp
    -Wno-deprecated-declarations # acpp error (v24.10.0) with -Werror
    --acpp-targets=omp
    # TODO: make clang version configurable?
    --acpp-clang=/usr/bin/clang++-18
)
add_link_options(
    --acpp-targets=omp
    --acpp-clang=/usr/bin/clang++-18
)