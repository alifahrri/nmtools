set(CMAKE_C_COMPILER /usr/local/bin/syclcc)
set(CMAKE_CXX_COMPILER /usr/local/bin/syclcc)

SET (CMAKE_C_COMPILER_WORKS 1)
add_compile_options(-W -Wall -Werror -Wextra -Wno-gnu-string-literal-operator-template -fopenmp
    --acpp-targets=omp
    --acpp-clang=/usr/bin/clang++-14
)
add_link_options(
    --acpp-targets=omp
    --acpp-clang=/usr/bin/clang++-14
)