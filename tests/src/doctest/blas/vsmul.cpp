// NOTE: seems like it is required to include these headers first
// TODO: fix dependency
#include "nmtools/array/fixed.hpp"
#include "nmtools/array/dynamic.hpp"
#include "testing/data/blas/vsmul.hpp"
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
 * @test test cases for vsmul
 * 
 */
TEST_CASE("blas::vsmul")
{
    NMTOOLS_TESTING_DECLARE_SUBCASES2(case1, blas::vsmul, expect::res, args::x, args::y);
    NMTOOLS_TESTING_DEC_RAW_SUBCASES2(case1, blas::vsmul, expect::res, args::v5, args::h);
    NMTOOLS_TESTING_DECLARE_SUBCASES2(case2, blas::vsmul, expect::res, args::x, args::y);
    NMTOOLS_TESTING_DEC_RAW_SUBCASES2(case2, blas::vsmul, expect::res, args::v10, args::h);
    NMTOOLS_TESTING_DECLARE_SUBCASES2(case3, blas::vsmul, expect::res, args::x, args::y);
    NMTOOLS_TESTING_DEC_RAW_SUBCASES2(case3, blas::vsmul, expect::res, args::v15, args::h);
    NMTOOLS_TESTING_DECLARE_SUBCASES2(case4, blas::vsmul, expect::res, args::x, args::y);
    NMTOOLS_TESTING_DEC_RAW_SUBCASES2(case4, blas::vsmul, expect::res, args::v20, args::h);
    NMTOOLS_TESTING_DECLARE_SUBCASES2(case5, blas::vsmul, expect::res, args::x, args::y);
    NMTOOLS_TESTING_DEC_RAW_SUBCASES2(case5, blas::vsmul, expect::res, args::v25, args::h);
}