#include "nmtools/array/index/nonzero.hpp"
#include "nmtools/array/ndarray/dynamic.hpp"
#include "nmtools/array/ndarray/hybrid.hpp"
#include "nmtools/array/ndarray/fixed.hpp"

#include "testing/doctest.hpp"

#include <vector>
#include <array>
#include <tuple>

namespace nm = nmtools;
namespace na = nm::array;
namespace meta = nm::meta;

NMTOOLS_TESTING_DECLARE_CASE(nonzero)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        int x[6] = {0,1,2,3,4,5};
        auto x_vector = cast<std::vector<int>>(x);
        auto x_array  = cast<int>(x);
        auto x_hybrid = cast<na::hybrid_ndarray<int,6,1>>(x);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        int result[5] = {1,2,3,4,5};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        int x[6] = {1,2,0,3,5,6};
        auto x_vector = cast<std::vector<int>>(x);
        auto x_array  = cast<int>(x);
        auto x_hybrid = cast<na::hybrid_ndarray<int,6,1>>(x);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        int result[5] = {0,1,3,4,5};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        bool x[6] = {true,true,false,true,true,true};
        auto x_vector = cast<std::vector<bool>>(x);
        auto x_array  = cast<bool>(x);
        auto x_hybrid = cast<na::hybrid_ndarray<int,6,1>>(x);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        int result[5] = {0,1,3,4,5};
    }
}

#define NONZERO_SUBCASE(case_name, x) \
SUBCASE(#case_name) \
{ \
    NMTOOLS_TESTING_DECLARE_NS(nonzero, case_name); \
    auto result = nm::index::nonzero(args::x); \
    NMTOOLS_ASSERT_EQUAL( result, expect::result ); \
} \

TEST_CASE("nonzero(vector)" * doctest::test_suite("index::nonzero"))
{
    NONZERO_SUBCASE( case1, x_vector );
    NONZERO_SUBCASE( case2, x_vector );
    NONZERO_SUBCASE( case3, x_vector );
}

TEST_CASE("nonzero(array)" * doctest::test_suite("index::nonzero"))
{
    NONZERO_SUBCASE( case1, x_array );
    NONZERO_SUBCASE( case2, x_array );
    NONZERO_SUBCASE( case3, x_array );
}

TEST_CASE("nonzero(hybrid_ndarray)" * doctest::test_suite("index::nonzero"))
{
    NONZERO_SUBCASE( case1, x_hybrid );
    NONZERO_SUBCASE( case2, x_hybrid );
    NONZERO_SUBCASE( case3, x_hybrid );
}