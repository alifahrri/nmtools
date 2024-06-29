// TODO: support dynamic size array for at
#define NMTOOLS_TEST_SKIP_DYNAMIC_SIZE_ARRAY
// NOTE: seems like it is required to include these headers first
// TODO: fix dependency
#include "nmtools/array/fixed.hpp"
#include "nmtools/array/dynamic.hpp"
#include "nmtools/array/utility/apply_at.hpp"
#include "nmtools/testing/doctest.hpp"

#include <array>
#include <vector>

/**
 * @brief define testing using doctest
 * 
 */
#define NMTOOLS_ASSERT_CLOSE NMTOOLS_ASSERT_CLOSE_DOCTEST

using nmtools_list, nmtools_array, nmtools_tuple;
namespace nm = nmtools;

TEST_CASE("apply_at(double[]...)" * doctest::test_suite("utility"))
{
    {
        double array[1] = {1};
        auto indices = nmtools_tuple{0};
        auto a = nm::apply_at(array, indices);
        NMTOOLS_ASSERT_CLOSE(a, 1);
    }
    {
        double array[2] = {1, 2};
        auto indices = nmtools_tuple{1};
        auto a = nm::apply_at(array, indices);
        NMTOOLS_ASSERT_CLOSE(a, 2);
    }
    {
        double array[3] = {1, 3, 2};
        auto indices = nmtools_tuple{1};
        auto a = nm::apply_at(array, indices);
        NMTOOLS_ASSERT_CLOSE(a, 3);
    }
    {
        double array[1][1][1][1][1] = {{{{{1}}}}};
        auto indices = nmtools_tuple{0,0,0,0,0};
        auto a = nm::apply_at(array, indices);
        NMTOOLS_ASSERT_CLOSE(a, 1);
    }
    {
        double array[1][2][1] = {{{0},{1}}};
        {
            auto indices = nmtools_tuple{0,0,0};
            auto a = nm::apply_at(array, indices);
            NMTOOLS_ASSERT_CLOSE(a, 0);
        }
        {
            auto indices = nmtools_tuple{0,1,0};
            auto a = nm::apply_at(array, indices);
            NMTOOLS_ASSERT_CLOSE(a, 1);
        }
    }
}

#ifndef NMTOOLS_DISABLE_STL
TEST_CASE("apply_at(std::array<...>)" * doctest::test_suite("utility"))
{
    {
        auto a = array{
            array{1,2},
            array{3,4},
        };
        {
            auto indices = nmtools_tuple{0,1};
            auto res = nm::apply_at(a,indices);
            NMTOOLS_ASSERT_CLOSE(res, 2);
        }
        {
            auto indices = nmtools_tuple{1,0};
            auto res = nm::apply_at(a,indices);
            NMTOOLS_ASSERT_CLOSE(res, 3);
        }
        {
            auto indices = nmtools_tuple{1,1};
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
            auto indices = nmtools_tuple{0,0,0};
            auto res = nm::apply_at(a,indices);
            NMTOOLS_ASSERT_CLOSE(res, 1);
        }
        {
            auto indices = nmtools_tuple{0,1,0};
            auto res = nm::apply_at(a,indices);
            NMTOOLS_ASSERT_CLOSE(res, 3);
        }
        {
            auto indices = nmtools_tuple{1,0,0};
            auto res = nm::apply_at(a,indices);
            NMTOOLS_ASSERT_CLOSE(res, 5);
        }
        {
            auto indices = nmtools_tuple{1,1,1};
            auto res = nm::apply_at(a,indices);
            NMTOOLS_ASSERT_CLOSE(res, 8);
        }
    }
}

TEST_CASE("apply_at(std::vector<...>)" * doctest::test_suite("utility"))
{
    {
        auto a = vector{
            vector{1,2},
            vector{3,4},
        };
        {
            auto indices = nmtools_tuple{0,1};
            auto res = nm::apply_at(a,indices);
            NMTOOLS_ASSERT_CLOSE(res, 2);
        }
        {
            auto indices = nmtools_tuple{1,0};
            auto res = nm::apply_at(a,indices);
            NMTOOLS_ASSERT_CLOSE(res, 3);
        }
        {
            auto indices = nmtools_tuple{1,1};
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
            auto indices = nmtools_tuple{0,0,0};
            auto res = nm::apply_at(a,indices);
            NMTOOLS_ASSERT_CLOSE(res, 1);
        }
        {
            auto indices = nmtools_tuple{0,1,0};
            auto res = nm::apply_at(a,indices);
            NMTOOLS_ASSERT_CLOSE(res, 3);
        }
        {
            auto indices = nmtools_tuple{1,0,0};
            auto res = nm::apply_at(a,indices);
            NMTOOLS_ASSERT_CLOSE(res, 5);
        }
        {
            auto indices = nmtools_tuple{1,1,1};
            auto res = nm::apply_at(a,indices);
            NMTOOLS_ASSERT_CLOSE(res, 8);
        }
    }
}

TEST_CASE("apply_at(dynamic_ndarray<>)" * doctest::test_suite("utility"))
{
    using nm::array::dynamic_ndarray;
    {
        auto a = dynamic_ndarray{{1,2,3,4,5,6}};
        {
            auto indices = nmtools_tuple{1};
            auto res = nm::apply_at(a, indices);
            NMTOOLS_ASSERT_CLOSE(res, 2);
        }
        {
            auto indices = nmtools_tuple{2};
            auto res = nm::apply_at(a, indices);
            NMTOOLS_ASSERT_CLOSE(res, 3);
        }
    }
}
#endif // NMTOOLS_DISABLE_STL

TEST_CASE("apply_at(dynamic_ndarray<>)" * doctest::test_suite("utility"))
{
    using nm::array::dynamic_ndarray;
    {
        auto a = dynamic_ndarray{{1,2,3,4,5,6}};
        {
            // utl::vector tripped for 1 element
            // TODO: fix utl vector initialization with 1 element
            #if 0
            auto indices = vector{1ul};
            #else
            auto indices = vector<size_t>(1);
            indices[0] = 1;
            #endif
            auto res = nm::apply_at(a, indices);
            NMTOOLS_ASSERT_CLOSE(res, 2);
        }
        {
            // TODO: fix utl vector initialization with 1 element
            #if 0
            auto indices = vector{2ul};
            #else
            auto indices = vector<size_t>(1);
            indices[0] = 2;
            #endif
            auto res = nm::apply_at(a, indices);
            NMTOOLS_ASSERT_CLOSE(res, 3);
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
            auto indices = nmtools_tuple{0,1,0};
            auto res = nm::apply_at(a, indices);
            NMTOOLS_ASSERT_CLOSE(res, 2);
        }
        {
            auto indices = nmtools_tuple{1,0,0};
            auto res = nm::apply_at(a, indices);
            NMTOOLS_ASSERT_CLOSE(res, 3);
        }
        {
            auto indices = nmtools_tuple{2,1,0};
            auto res = nm::apply_at(a, indices);
            NMTOOLS_ASSERT_CLOSE(res, 6);
        }
    }
}