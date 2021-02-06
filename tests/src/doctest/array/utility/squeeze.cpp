// NOTE: seems like it is required to include these headers first
// TODO: fix dependency
#include "nmtools/array/dynamic.hpp"
#include "nmtools/array/utility.hpp"
#include "nmtools/array/fixed.hpp"
#include "testing/testing.hpp"
#include "testing/data/blas.hpp"
#include "testing/data/utility.hpp"
#include "testing/data/array/utility/squeeze.hpp"

#if __has_include("doctest/doctest.h")
    #include "doctest/doctest.h"
#else
   #include "doctest.h"
#endif

#include <array>
#include <vector>

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
namespace nmt = nmtools;
#define NMTOOLS_TEST_SUBCASE NMTOOLS_TESTING_DOCTEST_SUBCASE
#else
// TODO: rename to nmtools/bench/common.hpp or something
#include "common.hpp"
// TODO: rename to nmtools/bench/utility.hpp or something
#include "utility.hpp"
namespace nmt = nmtools::bench::nanobench;
#define NMTOOLS_TEST_SUBCASE NMTOOLS_BENCH_DOCTEST_SUBCASE
#endif

TEST_CASE("utility::squeeze")
{
    using nmt::squeeze;
    NMTOOLS_TESTING_DECLARE_SUBCASES(case1, squeeze, expect::res, args::x);
    NMTOOLS_TESTING_DECLARE_SUBCASES(case2, squeeze, expect::res, args::x);
    // NOTE: squeezing dynamic array returning 1D array while deferring error to runtime
    // causing isclose to complain about implementation when it can't be squeezed (should return 2D array)
    // TODO: fix, by either introduce dynamic n-dimensional array or provide view
    #undef NMTOOLS_TEST_SUBCASE_VECTOR
    #undef NMTOOLS_TEST_SUBCASE_DYNAMIC_ARRAY
    #define NMTOOLS_TEST_SUBCASE_VECTOR NMTOOLS_TEST_SUBCASE_NOOP
    #define NMTOOLS_TEST_SUBCASE_DYNAMIC_ARRAY NMTOOLS_TEST_SUBCASE_NOOP
    NMTOOLS_TESTING_DECLARE_SUBCASES(case3, squeeze, expect::res, args::x);
}