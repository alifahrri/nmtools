#include "nmtools/array/utility.hpp"
#include "nmtools/utility/helper.hpp"
#include <gtest/gtest.h>
#include <array>
#include <vector>

using std::array;
using std::vector;
namespace nmt = nmtools;
using nmt::helper::isclose;

TEST(array, at)
{
    using vector_t = array<double,3>;
    using matrix_t = array<vector_t,4>;
    using scalar_t = double;

    using dvector_t = std::vector<double>;

    /* compile-time version */
    {
        constexpr auto a = vector_t{
            {1.,   2.,  3.}
        };
        constexpr auto x = nmt::at(a,2);
        static_assert(std::is_same_v<decltype(x),const double>);
        static_assert(isclose(x,3.));
    }
    /* compile-time matrix version */
    {
        constexpr auto a = matrix_t{{
            {1.,   2.,  3.},
            {4.,   5.,  6.},
            {7.,   8.,  9.},
            {10., 11., 12.},
        }};
        constexpr auto x = nmt::at(a,3,2);
        static_assert(std::is_same_v<decltype(x),const double>);
        static_assert(isclose(x,12.));
    }
    /* runtime */
    {
        auto a = vector_t{
            {1.,   2.,  3.}
        };
        auto x = nmt::at(a,2);
        static_assert(std::is_same_v<decltype(x),double>);
        EXPECT_TRUE(isclose(x,3.));
    }
    /* runtime matrix */
    {
        auto a = matrix_t{{
            {1.,   2.,  3.},
            {4.,   5.,  6.},
            {7.,   8.,  9.},
            {10., 11., 12.},
        }};
        auto x = nmt::at(a,3,2);
        static_assert(std::is_same_v<decltype(x),double>);
        EXPECT_TRUE(isclose(x,12.));
    }
    /* vector assignment */
    {
        auto a = vector_t{
            {1.,   2.,  3.}
        };
        nmt::at(a,0) = 3.;
        nmt::at(a,2) = 1.;
        EXPECT_TRUE(isclose(a,vector_t{{3.,2.,1.}}));
    }
    /* matrix assignment */
    {
        auto a = matrix_t{{
            {1.,   2.,  3.},
            {4.,   5.,  6.},
            {7.,   8.,  9.},
            {10., 11., 12.},
        }};
        nmt::at(a,3,2) = 13.;
        auto e = matrix_t{{
            {1.,   2.,  3.},
            {4.,   5.,  6.},
            {7.,   8.,  9.},
            {10., 11., 13.},
        }};
        EXPECT_TRUE(isclose(a,e));
    }
}