#define NMTOOLS_TEST_SKIP_FIXED_SIZE_ARRAY
// NOTE: seems like it is required to include these headers first
// TODO: fix dependency
#include "nmtools/array/dynamic.hpp"
#include "nmtools/array/utility.hpp"
#include "nmtools/array/fixed.hpp"
#include "testing/testing.hpp"
#include "testing/data/blas.hpp"
#include "testing/data/utility.hpp"
#include "testing/data/array/utility/slice.hpp"

#include "doctest/doctest.h"

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

TEST_CASE("utility::slice")
{
    using nmt::slice;
    NMTOOLS_TESTING_DECLARE_TPARAM2_SUBCASES(case1, slice, args::start_t, args::stop_t, expect::res, args::x);
    NMTOOLS_TESTING_DECLARE_TPARAM2_SUBCASES(case2, slice, args::start_t, args::stop_t, expect::res, args::x);
    NMTOOLS_TESTING_DECLARE_TPARAM2_SUBCASES(case3, slice, args::start_t, args::stop_t, expect::res, args::x);
    NMTOOLS_TESTING_DECLARE_SUBCASES3(case1, slice, expect::res, args::x, args::start, args::stop );
    NMTOOLS_TESTING_DECLARE_SUBCASES3(case2, slice, expect::res, args::x, args::start, args::stop );
    NMTOOLS_TESTING_DECLARE_SUBCASES3(case3, slice, expect::res, args::x, args::start, args::stop );
    NMTOOLS_TESTING_DECLARE_SUBCASES3(case4, slice, expect::res, args::x, args::start, args::stop );
    NMTOOLS_TESTING_DECLARE_SUBCASES3(case5, slice, expect::res, args::x, args::start, args::stop );
    NMTOOLS_TESTING_DECLARE_SUBCASES3(case6, slice, expect::res, args::x, args::start, args::stop );
    NMTOOLS_TESTING_DECLARE_SUBCASES3(case7, slice, expect::res, args::x, args::start, args::stop );
    NMTOOLS_TESTING_DECLARE_SUBCASES3(case8, slice, expect::res, args::x, args::start, args::stop );
    NMTOOLS_TESTING_DECLARE_SUBCASES3(case9, slice, expect::res, args::x, args::start, args::stop );
    NMTOOLS_TESTING_DECLARE_SUBCASES3(case10, slice, expect::res, args::x, args::start, args::stop );
    NMTOOLS_TESTING_DECLARE_SUBCASES3(case11, slice, expect::res, args::x, args::start, args::stop );
    NMTOOLS_TESTING_DECLARE_SUBCASES3(case12, slice, expect::res, args::x, args::start, args::stop );
    NMTOOLS_TESTING_DECLARE_SUBCASES3(case13, slice, expect::res, args::x, args::start, args::stop );
    NMTOOLS_TESTING_DECLARE_SUBCASES3(case14, slice, expect::res, args::x, args::start, args::stop );
    NMTOOLS_TESTING_DECLARE_SUBCASES3(case15, slice, expect::res, args::x, args::start, args::stop );
    NMTOOLS_TESTING_DECLARE_SUBCASES3(case16, slice, expect::res, args::x, args::start, args::stop );
    NMTOOLS_TESTING_DECLARE_SUBCASES3(case17, slice, expect::res, args::x, args::start, args::stop );
    NMTOOLS_TESTING_DECLARE_SUBCASES3(case18, slice, expect::res, args::x, args::start, args::stop );

    // note reactvate testing for fixed size array
    #undef NMTOOLS_TEST_SUBCASE_ARRAY
    #undef NMTOOLS_TEST_SUBCASE_FIXED_ARRAY
    #define NMTOOLS_TEST_SUBCASE_ARRAY NMTOOLS_TEST_SUBCASE_ARRAY_IMPL
    #define NMTOOLS_TEST_SUBCASE_FIXED_ARRAY NMTOOLS_TEST_SUBCASE_FIXED_ARRAY_IMPL

    NMTOOLS_TESTING_DECLARE_TPARAM2_SUBCASES(case4, slice, args::start_indices_t, args::stop_indices_t, expect::res, args::x);
    NMTOOLS_TESTING_DECLARE_TPARAM2_SUBCASES(case5, slice, args::start_indices_t, args::stop_indices_t, expect::res, args::x);
    NMTOOLS_TESTING_DECLARE_TPARAM2_SUBCASES(case6, slice, args::start_indices_t, args::stop_indices_t, expect::res, args::x);
    NMTOOLS_TESTING_DECLARE_TPARAM2_SUBCASES(case7, slice, args::start_indices_t, args::stop_indices_t, expect::res, args::x);
    NMTOOLS_TESTING_DECLARE_TPARAM2_SUBCASES(case8, slice, args::start_indices_t, args::stop_indices_t, expect::res, args::x);
    // note the following relative benchmark table is no working properly may be because nmtools::end_t
    // TODO: fix benchmark table naming
    NMTOOLS_TESTING_DECLARE_TPARAM2_SUBCASES(case9, slice, args::start_indices_t, args::stop_indices_t, expect::res, args::x);
    NMTOOLS_TESTING_DECLARE_TPARAM2_SUBCASES(case10, slice, args::start_indices_t, args::stop_indices_t, expect::res, args::x);
    NMTOOLS_TESTING_DECLARE_TPARAM2_SUBCASES(case11, slice, args::start_indices_t, args::stop_indices_t, expect::res, args::x);
    NMTOOLS_TESTING_DECLARE_TPARAM2_SUBCASES(case12, slice, args::start_indices_t, args::stop_indices_t, expect::res, args::x);
    NMTOOLS_TESTING_DECLARE_TPARAM2_SUBCASES(case13, slice, args::start_indices_t, args::stop_indices_t, expect::res, args::x);
    NMTOOLS_TESTING_DECLARE_TPARAM2_SUBCASES(case14, slice, args::start_index_t, args::stop_index_t, expect::res, args::x);
    NMTOOLS_TESTING_DECLARE_TPARAM2_SUBCASES(case15, slice, args::start_index_t, args::stop_index_t, expect::res, args::x);
    NMTOOLS_TESTING_DECLARE_TPARAM2_SUBCASES(case16, slice, args::start_index_t, args::stop_index_t, expect::res, args::x);
    NMTOOLS_TESTING_DECLARE_TPARAM2_SUBCASES(case17, slice, args::start_index_t, args::stop_index_t, expect::res, args::x);
    NMTOOLS_TESTING_DECLARE_TPARAM2_SUBCASES(case18, slice, args::start_index_t, args::stop_index_t, expect::res, args::x);
}