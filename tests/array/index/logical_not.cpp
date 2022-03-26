#include "nmtools/array/index/logical_not.hpp"
#include "nmtools/array/ndarray/fixed.hpp"
#include "nmtools/array/ndarray/hybrid.hpp"
#include "nmtools/array/ndarray/dynamic.hpp"
#include "testing/doctest.hpp"

#include <vector>
#include <array>
#include <tuple>

namespace nm = nmtools;
namespace na = nm::array;
namespace meta = nm::meta;

NMTOOLS_TESTING_DECLARE_CASE(logical_not)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        bool x[5] = {true, false, false, true, false};
        auto x_vector = cast<std::vector<bool>>(x);
        auto x_array  = cast<bool>(x);
        auto x_fixed_vector = cast<na::fixed_ndarray<bool,5>>(x);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        bool x[5] = {false, true, true, false, true};
        auto x_vector = cast<std::vector<bool>>(x);
        auto x_array  = cast<bool>(x);
        auto x_fixed_vector = cast<na::fixed_ndarray<bool,5>>(x);
    }
}

// TEST_CASE("logical_not(raw)" * doctest::test_suite("index::logical_not"))
// {
//     NMTOOLS_TESTING_DECLARE_NS(logical_not, case1);
//     auto result = nm::index::logical_not(args::x);
//     auto expected = expect::x;
//     NMTOOLS_ASSERT_EQUAL( result, expected );
// }

TEST_CASE("logical_not(vector)" * doctest::test_suite("index::logical_not"))
{
    NMTOOLS_TESTING_DECLARE_NS(logical_not, case1);
    auto result = nm::index::logical_not(args::x_vector);
    auto expected = expect::x_vector;
    NMTOOLS_ASSERT_EQUAL( result, expected );
}

TEST_CASE("logical_not(array)" * doctest::test_suite("index::logical_not"))
{
    NMTOOLS_TESTING_DECLARE_NS(logical_not, case1);
    auto result = nm::index::logical_not(args::x_array);
    auto expected = expect::x_array;
    NMTOOLS_ASSERT_EQUAL( result, expected );
}


TEST_CASE("logical_not(fixed_vector)" * doctest::test_suite("index::logical_not"))
{
    NMTOOLS_TESTING_DECLARE_NS(logical_not, case1);
    auto result = nm::index::logical_not(args::x_fixed_vector);
    auto expected = expect::x_fixed_vector;
    NMTOOLS_ASSERT_EQUAL( result, expected );
}