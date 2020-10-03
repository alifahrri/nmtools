// NOTE: seems like it is required to include these headers first
// TODO: fix dependency
#include "nmtools/array/fixed.hpp"
#include "nmtools/array/dynamic.hpp"
// NOTE: need to include this so that std::to_string(nmtools::blas::norm_t) is visible
// TODO: fix dependency
#include "nmtools/blas/blas.hpp"
#include "testing/data/blas.hpp"
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
 * @test test cases for nmtools::blas::matrix_norm
 * @todo benchmark name is mixed-up for templated matrix_norm,
 * make different bench object for each norm type (different bench for 1,'fro','inf')!
 * 
 */
TEST_CASE("blas::matrix_norm")
{
    NMTOOLS_TESTING_DECLARE_TPARAM_SUBCASES(case1, blas::matrix_norm, args::p, expect::norm, args::x );
    NMTOOLS_TESTING_DEC_TPARAM_RAW_SUBCASES(case1, blas::matrix_norm, args::p, expect::norm, args::x );
    NMTOOLS_TESTING_DECLARE_TPARAM_SUBCASES(case2, blas::matrix_norm, args::p, expect::norm, args::x );
    NMTOOLS_TESTING_DEC_TPARAM_RAW_SUBCASES(case2, blas::matrix_norm, args::p, expect::norm, args::x );
    NMTOOLS_TESTING_DECLARE_TPARAM_SUBCASES(case3, blas::matrix_norm, args::p, expect::norm, args::x );
    NMTOOLS_TESTING_DEC_TPARAM_RAW_SUBCASES(case3, blas::matrix_norm, args::p, expect::norm, args::x );
    NMTOOLS_TESTING_DECLARE_TPARAM_SUBCASES(case4, blas::matrix_norm, args::p, expect::norm, args::x );
    NMTOOLS_TESTING_DEC_TPARAM_RAW_SUBCASES(case4, blas::matrix_norm, args::p, expect::norm, args::m5x5 );
    NMTOOLS_TESTING_DECLARE_TPARAM_SUBCASES(case5, blas::matrix_norm, args::p, expect::norm, args::x );
    NMTOOLS_TESTING_DEC_TPARAM_RAW_SUBCASES(case5, blas::matrix_norm, args::p, expect::norm, args::m10x10 );
    NMTOOLS_TESTING_DECLARE_TPARAM_SUBCASES(case6, blas::matrix_norm, args::p, expect::norm, args::x );
    NMTOOLS_TESTING_DEC_TPARAM_RAW_SUBCASES(case6, blas::matrix_norm, args::p, expect::norm, args::m15x15 );
    NMTOOLS_TESTING_DECLARE_TPARAM_SUBCASES(case7, blas::matrix_norm, args::p, expect::norm, args::x );
    NMTOOLS_TESTING_DEC_TPARAM_RAW_SUBCASES(case7, blas::matrix_norm, args::p, expect::norm, args::m20x20 );
    NMTOOLS_TESTING_DECLARE_TPARAM_SUBCASES(case8, blas::matrix_norm, args::p, expect::norm, args::x );
    NMTOOLS_TESTING_DEC_TPARAM_RAW_SUBCASES(case8, blas::matrix_norm, args::p, expect::norm, args::m25x25 );
}