// NOTE: seems like it is required to include these headers first
// TODO: fix dependency
#include "nmtools/array/fixed.hpp"
#include "nmtools/array/dynamic.hpp"
#include "testing/data/blas/gaxpy.hpp"
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
 * @brief test case for nmtools::blas::gaxpy
 * 
 */
TEST_CASE("blas::gaxpy")
{
    NMTOOLS_TESTING_DECLARE_SUBCASES3(case1, blas::gaxpy, expect::res, args::a, args::x, args::y);
    NMTOOLS_TESTING_DEC_RAW_SUBCASES3(case1, blas::gaxpy, expect::res, args::a, args::v5, args::r5);
    NMTOOLS_TESTING_DECLARE_SUBCASES3(case2, blas::gaxpy, expect::res, args::a, args::x, args::y);
    NMTOOLS_TESTING_DEC_RAW_SUBCASES3(case2, blas::gaxpy, expect::res, args::a, args::v10, args::r10);
    NMTOOLS_TESTING_DECLARE_SUBCASES3(case3, blas::gaxpy, expect::res, args::a, args::x, args::y);
    NMTOOLS_TESTING_DEC_RAW_SUBCASES3(case3, blas::gaxpy, expect::res, args::a, args::v15, args::r15);
    NMTOOLS_TESTING_DECLARE_SUBCASES3(case4, blas::gaxpy, expect::res, args::a, args::x, args::y);
    NMTOOLS_TESTING_DEC_RAW_SUBCASES3(case4, blas::gaxpy, expect::res, args::a, args::v20, args::r20);
    NMTOOLS_TESTING_DECLARE_SUBCASES3(case5, blas::gaxpy, expect::res, args::a, args::x, args::y);
    NMTOOLS_TESTING_DEC_RAW_SUBCASES3(case5, blas::gaxpy, expect::res, args::a, args::v25, args::r25);
}