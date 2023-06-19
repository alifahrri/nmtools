set(CMAKE_C_COMPILER /usr/local/bin/syclcc)
set(CMAKE_CXX_COMPILER /usr/local/bin/syclcc)

SET (CMAKE_C_COMPILER_WORKS 1)
add_compile_options(-W -Wall -Werror -Wextra -Wno-gnu-string-literal-operator-template --hipsycl-targets=omp --hipsycl-clang=/usr/bin/clang++-14)