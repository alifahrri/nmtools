// TODO: support dynamic size array for at
#define NMTOOLS_TEST_SKIP_DYNAMIC_SIZE_ARRAY
// NOTE: seems like it is required to include these headers first
// TODO: fix dependency
#include "nmtools/array/fixed.hpp"
#include "nmtools/array/dynamic.hpp"
#include "nmtools/constants.hpp"
#include "testing/testing.hpp"
#include "testing/data/blas.hpp"
#include "testing/data/array/utility/at.hpp"

#include "testing/doctest.hpp"

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
namespace nm = nmtools;
#define NMTOOLS_TEST_SUBCASE NMTOOLS_TESTING_DOCTEST_SUBCASE
#else
// TODO: rename to nmtools/bench/common.hpp or something
#include "common.hpp"
// TODO: rename to nmtools/bench/utility.hpp or something
#include "utility.hpp"
namespace nm = nmtools::bench::nanobench;
#define NMTOOLS_TEST_SUBCASE NMTOOLS_BENCH_DOCTEST_SUBCASE
#endif

TEST_CASE("utility::at")
{
    using nm::at;
    NMTOOLS_TESTING_DECLARE_SUBCASES3( case1, at, expect::res, args::x, args::i, args::j );
}

TEST_CASE("at" * doctest::test_suite("utility"))
{
    namespace nm = nmtools;

    {
        auto array  = std::array{1,2,3,4};
        auto result = nm::at<2>(array);
        NMTOOLS_ASSERT_CLOSE( result, 3 );
    }
    {
        auto array  = std::tuple{1,2,3,4};
        auto result = nm::at<2>(array);
        NMTOOLS_ASSERT_CLOSE( result, 3 );
    }
    {
        auto array  = std::vector{1,2,3,4};
        auto result = nm::at<2>(array);
        NMTOOLS_ASSERT_CLOSE( result, 3 );
    }
    {
        auto array  = std::array{1,2,3,4};
        nm::at<2>(array) = 5;
        NMTOOLS_ASSERT_CLOSE( array, (std::array{1,2,5,4}) );
    }
    {
        auto array  = std::tuple{1,2,3,4};
        nm::at<2>(array) = 5;
        NMTOOLS_ASSERT_CLOSE( array, (std::array{1,2,5,4}) );
    }
    {
        auto array  = std::vector{1,2,3,4};
        nm::at<2>(array) = 5;
        NMTOOLS_ASSERT_CLOSE( array, (std::array{1,2,5,4}) );
    }

    using namespace nm::literals;
    {
        auto array  = std::array{1,2,3,4};
        auto index  = 2_ct;
        auto result = nm::at(array, index);
        NMTOOLS_ASSERT_CLOSE( result, 3 );
    }
    {
        auto array  = std::tuple{1,2,3,4};
        auto index  = 2_ct;
        auto result = nm::at(array, index);
        NMTOOLS_ASSERT_CLOSE( result, 3 );
    }
    {
        auto array  = std::vector{1,2,3,4};
        auto index  = 2_ct;
        auto result = nm::at(array, index);
        NMTOOLS_ASSERT_CLOSE( result, 3 );
    }
    {
        auto array  = std::array{1,2,3,4};
        auto index  = 2_ct;
        nm::at(array, index) = 5;
        NMTOOLS_ASSERT_CLOSE( array, (std::array{1,2,5,4}) );
    }
    {
        auto array  = std::tuple{1,2,3,4};
        auto index  = 2_ct;
        nm::at(array, index) = 5;
        NMTOOLS_ASSERT_CLOSE( array, (std::array{1,2,5,4}) );
    }
    {
        auto array  = std::vector{1,2,3,4};
        auto index  = 2_ct;
        nm::at(array, index) = 5;
        NMTOOLS_ASSERT_CLOSE( array, (std::array{1,2,5,4}) );
    }
}