// NOTE: seems like it is required to include these headers first
// TODO: fix dependency
#include "nmtools/array/fixed.hpp"
#include "nmtools/array/dynamic.hpp"
// NOTE: need to include this so that std::to_string(nmtools::blas::norm_t) is visible
// TODO: fix dependency
#include "nmtools/blas/blas.hpp"
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
 * @test test cases for nmtools::blas::vector_norm
 * @todo benchmark name is mixed-up for templated vector_norm,
 * make different bench object for each norm type (different bench for 1,2,'inf')!
 * 
 */
TEST_CASE("blas::vector_norm")
{
    NMTOOLS_TESTING_DECLARE_TPARAM_SUBCASES(case1, blas::vector_norm, args::p, expect::norm, args::x);
    NMTOOLS_TESTING_DEC_TPARAM_RAW_SUBCASES(case1, blas::vector_norm, args::p, expect::norm, args::x);
    NMTOOLS_TESTING_DECLARE_TPARAM_SUBCASES(case2, blas::vector_norm, args::p, expect::norm, args::x);
    NMTOOLS_TESTING_DEC_TPARAM_RAW_SUBCASES(case2, blas::vector_norm, args::p, expect::norm, args::x);
    NMTOOLS_TESTING_DECLARE_TPARAM_SUBCASES(case3, blas::vector_norm, args::p, expect::norm, args::x);
    NMTOOLS_TESTING_DEC_TPARAM_RAW_SUBCASES(case3, blas::vector_norm, args::p, expect::norm, args::x);
}