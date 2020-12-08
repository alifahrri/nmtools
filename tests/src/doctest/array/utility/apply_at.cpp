// TODO: support dynamic size array for at
#define NMTOOLS_TEST_SKIP_DYNAMIC_SIZE_ARRAY
// NOTE: seems like it is required to include these headers first
// TODO: fix dependency
#include "nmtools/array/fixed.hpp"
#include "nmtools/array/dynamic.hpp"
#include "nmtools/array/utility/apply_at.hpp"
#include "testing/testing.hpp"
#include "testing/data/array/utility/apply_at.hpp"

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
namespace nm  = nmtools;
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

using std::tuple;
using std::vector;

TEST_CASE("apply_at(double[]...)" * doctest::test_suite("utility"))
{
    {
        double array[1] = {1};
        auto indices = tuple{0};
        auto a = nm::apply_at(array, indices);
        NMTOOLS_ASSERT_CLOSE(a, 1);
    }
    {
        double array[2] = {1, 2};
        auto indices = tuple{1};
        auto a = nm::apply_at(array, indices);
        NMTOOLS_ASSERT_CLOSE(a, 2);
    }
    {
        double array[3] = {1, 3, 2};
        auto indices = tuple{1};
        auto a = nm::apply_at(array, indices);
        NMTOOLS_ASSERT_CLOSE(a, 3);
    }
    {
        double array[1][1][1][1][1] = {{{{{1}}}}};
        auto indices = tuple{0,0,0,0,0};
        auto a = nm::apply_at(array, indices);
        NMTOOLS_ASSERT_CLOSE(a, 1);
    }
    {
        double array[1][2][1] = {{{0},{1}}};
        {
            auto indices = tuple{0,0,0};
            auto a = nm::apply_at(array, indices);
            NMTOOLS_ASSERT_CLOSE(a, 0);
        }
        {
            auto indices = tuple{0,1,0};
            auto a = nm::apply_at(array, indices);
            NMTOOLS_ASSERT_CLOSE(a, 1);
        }
    }
}

TEST_CASE("apply_at(std::array<...>)" * doctest::test_suite("utility"))
{
    using std::array;
    {
        auto a = array{
            array{1,2},
            array{3,4},
        };
        {
            auto indices = tuple{0,1};
            auto res = nm::apply_at(a,indices);
            NMTOOLS_ASSERT_CLOSE(res, 2);
        }
        {
            auto indices = tuple{1,0};
            auto res = nm::apply_at(a,indices);
            NMTOOLS_ASSERT_CLOSE(res, 3);
        }
        {
            auto indices = tuple{1,1};
            auto res = nm::apply_at(a,indices);
            NMTOOLS_ASSERT_CLOSE(res, 4);
        }
    }
    {
        auto a = array{
            array{ array{1,2}, array{3,4}, },
            array{ array{5,6}, array{7,8}, },
        };
        {
            auto indices = tuple{0,0,0};
            auto res = nm::apply_at(a,indices);
            NMTOOLS_ASSERT_CLOSE(res, 1);
        }
        {
            auto indices = tuple{0,1,0};
            auto res = nm::apply_at(a,indices);
            NMTOOLS_ASSERT_CLOSE(res, 3);
        }
        {
            auto indices = tuple{1,0,0};
            auto res = nm::apply_at(a,indices);
            NMTOOLS_ASSERT_CLOSE(res, 5);
        }
        {
            auto indices = tuple{1,1,1};
            auto res = nm::apply_at(a,indices);
            NMTOOLS_ASSERT_CLOSE(res, 8);
        }
    }
}

TEST_CASE("apply_at(std::vector<...>)" * doctest::test_suite("utility"))
{
    using std::vector;
    {
        auto a = vector{
            vector{1,2},
            vector{3,4},
        };
        {
            auto indices = tuple{0,1};
            auto res = nm::apply_at(a,indices);
            NMTOOLS_ASSERT_CLOSE(res, 2);
        }
        {
            auto indices = tuple{1,0};
            auto res = nm::apply_at(a,indices);
            NMTOOLS_ASSERT_CLOSE(res, 3);
        }
        {
            auto indices = tuple{1,1};
            auto res = nm::apply_at(a,indices);
            NMTOOLS_ASSERT_CLOSE(res, 4);
        }
    }
    {
        auto a = vector{
            vector{ vector{1,2}, vector{3,4}, },
            vector{ vector{5,6}, vector{7,8}, },
        };
        {
            auto indices = tuple{0,0,0};
            auto res = nm::apply_at(a,indices);
            NMTOOLS_ASSERT_CLOSE(res, 1);
        }
        {
            auto indices = tuple{0,1,0};
            auto res = nm::apply_at(a,indices);
            NMTOOLS_ASSERT_CLOSE(res, 3);
        }
        {
            auto indices = tuple{1,0,0};
            auto res = nm::apply_at(a,indices);
            NMTOOLS_ASSERT_CLOSE(res, 5);
        }
        {
            auto indices = tuple{1,1,1};
            auto res = nm::apply_at(a,indices);
            NMTOOLS_ASSERT_CLOSE(res, 8);
        }
    }
}

TEST_CASE("apply_at(fixed_vector<>)" * doctest::test_suite("utility"))
{
    using nm::array::fixed_vector;
    {
        auto a = fixed_vector({1,2,3,4,5,6});
        {
            auto indices = tuple{1};
            auto res = nm::apply_at(a, indices);
            NMTOOLS_ASSERT_CLOSE(res, 2);
        }
        {
            auto indices = tuple{2};
            auto res = nm::apply_at(a, indices);
            NMTOOLS_ASSERT_CLOSE(res, 3);
        }
    }
}

TEST_CASE("apply_at(dynamic_vector<>)" * doctest::test_suite("utility"))
{
    using nm::array::dynamic_vector;
    {
        auto a = dynamic_vector<double>{1,2,3,4,5,6};
        {
            auto indices = tuple{1};
            auto res = nm::apply_at(a, indices);
            NMTOOLS_ASSERT_CLOSE(res, 2);
        }
        {
            auto indices = tuple{2};
            auto res = nm::apply_at(a, indices);
            NMTOOLS_ASSERT_CLOSE(res, 3);
        }
    }
}

TEST_CASE("apply_at(dynamic_ndarray<>)" * doctest::test_suite("utility"))
{
    using nm::array::dynamic_ndarray;
    {
        auto a = dynamic_ndarray{{1,2,3,4,5,6}};
        {
            auto indices = tuple{1};
            auto res = nm::apply_at(a, indices);
            NMTOOLS_ASSERT_CLOSE(res, 2);
        }
        {
            auto indices = tuple{2};
            auto res = nm::apply_at(a, indices);
            NMTOOLS_ASSERT_CLOSE(res, 3);
        }
    }
}

TEST_CASE("apply_at(dynamic_ndarray<>)" * doctest::test_suite("utility"))
{
    using nm::array::dynamic_ndarray;
    {
        auto a = dynamic_ndarray{{1,2,3,4,5,6}};
        {
            auto indices = vector{1ul};
            auto res = nm::apply_at(a, indices);
            NMTOOLS_ASSERT_CLOSE(res, 2);
        }
        {
            auto indices = vector{2ul};
            auto res = nm::apply_at(a, indices);
            NMTOOLS_ASSERT_CLOSE(res, 3);
        }
    }
}

TEST_CASE("apply_at(fixed_matrix<>)" * doctest::test_suite("utility"))
{
    using nm::array::fixed_matrix;
    {
        // fixed_matrix<double,3,2>
        auto a = fixed_matrix({
            {1,2},
            {3,4},
            {5,6}
        });
        {
            auto indices = tuple{0,1};
            auto res = nm::apply_at(a, indices);
            NMTOOLS_ASSERT_CLOSE(res, 2);
        }
        {
            auto indices = tuple{1,0};
            auto res = nm::apply_at(a, indices);
            NMTOOLS_ASSERT_CLOSE(res, 3);
        }
        {
            auto indices = tuple{2,1};
            auto res = nm::apply_at(a, indices);
            NMTOOLS_ASSERT_CLOSE(res, 6);
        }
    }
}

TEST_CASE("apply_at(dynamic_matrix<>)" * doctest::test_suite("utility"))
{
    using nm::array::dynamic_matrix;
    {
        auto a = dynamic_matrix{ {1,2}, {3,4}, {5,6} };
        {
            auto indices = tuple{0,1};
            auto res = nm::apply_at(a, indices);
            NMTOOLS_ASSERT_CLOSE(res, 2);
        }
        {
            auto indices = tuple{1,0};
            auto res = nm::apply_at(a, indices);
            NMTOOLS_ASSERT_CLOSE(res, 3);
        }
        {
            auto indices = tuple{2,1};
            auto res = nm::apply_at(a, indices);
            NMTOOLS_ASSERT_CLOSE(res, 6);
        }
    }
}

TEST_CASE("apply_at(dynamic_ndarray<>)" * doctest::test_suite("utility"))
{
    using nm::array::dynamic_ndarray;
    {
        auto a = dynamic_ndarray({ {1,2}, {3,4}, {5,6} });
        {
            auto indices = vector{0ul,1ul};
            auto res = nm::apply_at(a, indices);
            NMTOOLS_ASSERT_CLOSE(res, 2);
        }
        {
            auto indices = vector{1ul,0ul};
            auto res = nm::apply_at(a, indices);
            NMTOOLS_ASSERT_CLOSE(res, 3);
        }
        {
            auto indices = vector{2ul,1ul};
            auto res = nm::apply_at(a, indices);
            NMTOOLS_ASSERT_CLOSE(res, 6);
        }
    }
}

TEST_CASE("apply_at(fixed_ndarray<>)" * doctest::test_suite("utility"))
{
    using nm::array::fixed_ndarray;
    {
        // auto a = fixed_ndarray<double,3,2,1>{};
        // a = { {{1},{2}}, {{3},{4}}, {{5},{6}} };
        auto a = fixed_ndarray{
            { {{1},{2}}, {{3},{4}}, {{5},{6}} }
        };
        {
            auto indices = tuple{0,1,0};
            auto res = nm::apply_at(a, indices);
            NMTOOLS_ASSERT_CLOSE(res, 2);
        }
        {
            auto indices = tuple{1,0,0};
            auto res = nm::apply_at(a, indices);
            NMTOOLS_ASSERT_CLOSE(res, 3);
        }
        {
            auto indices = tuple{2,1,0};
            auto res = nm::apply_at(a, indices);
            NMTOOLS_ASSERT_CLOSE(res, 6);
        }
    }
}