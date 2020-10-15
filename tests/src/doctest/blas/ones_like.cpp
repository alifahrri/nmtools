// @note seems like it is required to include these headers first
// @note include dynamic first to make specialization of matrix_size/vector_size of dynamic_matrix etc visible!!!
// @todo fix dependency
#include "nmtools/array/dynamic.hpp"
#include "nmtools/array/fixed.hpp"
#include "testing/data/blas/ones_like.hpp"
#include "doctest/doctest.h"

/**
 * @brief define testing using doctest
 * 
 */
#define NMTOOLS_ASSERT_CLOSE NMTOOLS_ASSERT_CLOSE_DOCTEST

/**
 * @brief check if we should disable benchmark
 * 
 */
#ifdef NMTOOLS_TESTING_DOCTEST_DISABLE_BENCH
namespace blas = nmtools::blas;
#define NMTOOLS_TEST_SUBCASE NMTOOLS_TESTING_DOCTEST_SUBCASE
#else
// TODO: rename to nmtools/bench/common.hpp or something
#include "common.hpp"
// TODO: rename to nmtools/bench/blas.hpp or something
#include "blas.hpp"
namespace blas = nmtools::bench::nanobench::blas;
#define NMTOOLS_TEST_SUBCASE NMTOOLS_BENCH_DOCTEST_SUBCASE
#endif

/**
 * @test test cases for ones_like
 * 
 */
TEST_CASE("blas::ones_like")
{
    NMTOOLS_TESTING_DECLARE_SUBCASES(case1, blas::ones_like, expect::x, args::x );
    NMTOOLS_TESTING_DEC_RAW_SUBCASES(case1, blas::ones_like, expect::x, args::z5x5 );
    NMTOOLS_TESTING_DECLARE_SUBCASES(case2, blas::ones_like, expect::x, args::x );
    NMTOOLS_TESTING_DEC_RAW_SUBCASES(case2, blas::ones_like, expect::x, args::z10x10 );
    NMTOOLS_TESTING_DECLARE_SUBCASES(case3, blas::ones_like, expect::x, args::x );
    NMTOOLS_TESTING_DEC_RAW_SUBCASES(case3, blas::ones_like, expect::x, args::z15x15 );
    NMTOOLS_TESTING_DECLARE_SUBCASES(case4, blas::ones_like, expect::x, args::x );
    NMTOOLS_TESTING_DEC_RAW_SUBCASES(case4, blas::ones_like, expect::x, args::z20x20 );
    NMTOOLS_TESTING_DECLARE_SUBCASES(case5, blas::ones_like, expect::x, args::x );
    NMTOOLS_TESTING_DEC_RAW_SUBCASES(case5, blas::ones_like, expect::x, args::z25x25 );
} // TEST_CASE("blas::ones_like")