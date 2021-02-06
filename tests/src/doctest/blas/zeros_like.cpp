// NOTE: seems like it is required to include these headers first
// TODO: fix dependency
#include "nmtools/array/fixed.hpp"
#include "nmtools/array/dynamic.hpp"
#include "testing/data/blas.hpp"
#if __has_include("doctest/doctest.h")
    #include "doctest/doctest.h"
#else
   #include "doctest.h"
#endif

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
 * @test test cases for zeros_like
 * 
 */
TEST_CASE("blas::zeros_like")
{
    NMTOOLS_TESTING_DECLARE_SUBCASES(case1, blas::zeros_like, expect::x, args::x );
    NMTOOLS_TESTING_DEC_RAW_SUBCASES(case1, blas::zeros_like, expect::x, args::x3 );
    NMTOOLS_TESTING_DECLARE_SUBCASES(case2, blas::zeros_like, expect::x, args::x );
    NMTOOLS_TESTING_DEC_RAW_SUBCASES(case2, blas::zeros_like, expect::x, args::o3x3 );
    NMTOOLS_TESTING_DECLARE_SUBCASES(case3, blas::zeros_like, expect::x, args::x );
    NMTOOLS_TESTING_DEC_RAW_SUBCASES(case3, blas::zeros_like, expect::x, args::o5x5 );
    NMTOOLS_TESTING_DECLARE_SUBCASES(case4, blas::zeros_like, expect::x, args::x );
    NMTOOLS_TESTING_DEC_RAW_SUBCASES(case4, blas::zeros_like, expect::x, args::o10x10 );
    NMTOOLS_TESTING_DECLARE_SUBCASES(case5, blas::zeros_like, expect::x, args::x );
    NMTOOLS_TESTING_DEC_RAW_SUBCASES(case5, blas::zeros_like, expect::x, args::o15x15 );
    NMTOOLS_TESTING_DECLARE_SUBCASES(case6, blas::zeros_like, expect::x, args::x );
    NMTOOLS_TESTING_DEC_RAW_SUBCASES(case6, blas::zeros_like, expect::x, args::o20x20 );
    NMTOOLS_TESTING_DECLARE_SUBCASES(case7, blas::zeros_like, expect::x, args::x );
    NMTOOLS_TESTING_DEC_RAW_SUBCASES(case7, blas::zeros_like, expect::x, args::o25x25 );
} // TEST_CASE("blas::zeros_like")