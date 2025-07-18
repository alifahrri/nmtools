#ifndef NMTOOLS_TESTING_DATA_ARRAY_RELU_HPP
#define NMTOOLS_TESTING_DATA_ARRAY_RELU_HPP

#include "nmtools/testing/testing.hpp"
#include "nmtools/testing/array_cast.hpp"

namespace nm = nmtools;
namespace na = nmtools;
namespace kind = na::kind;

#ifndef NMTOOLS_BUILD_CONSTEXPR_TESTS

NMTOOLS_TESTING_DECLARE_CASE(activations, relu)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline float a[2][3][2] = {{{-9.0000, -7.3636},
         {-5.7273, -4.0909},
         {-2.4545, -0.8182}},

        {{ 0.8182,  2.4545},
         { 4.0909,  5.7273},
         { 7.3636,  9.0000}}};
        NMTOOLS_CAST_ARRAYS(a);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline float result[2][3][2] = {{{0.0000, 0.0000},
         {0.0000, 0.0000},
         {0.0000, 0.0000}},

        {{0.8182, 2.4545},
         {4.0909, 5.7273},
         {7.3636, 9.0000}}};
    }
}

#else  // NMTOOLS_BUILD_CONSTEXPR_TESTS

NMTOOLS_TESTING_DECLARE_CASE(activations, constexpr_relu)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        constexpr inline float a[2][3][2] = {{{-9.0000, -7.3636},
         {-5.7273, -4.0909},
         {-2.4545, -0.8182}},

        {{ 0.8182,  2.4545},
         { 4.0909,  5.7273},
         { 7.3636,  9.0000}}};
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(a);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        constexpr inline float result[2][3][2] = {{{0.0000, 0.0000},
         {0.0000, 0.0000},
         {0.0000, 0.0000}},

        {{0.8182, 2.4545},
         {4.0909, 5.7273},
         {7.3636, 9.0000}}};
    }
}

#endif // NMTOOLS_BUILD_CONSTEXPR_TESTS

#endif // NMTOOLS_TESTING_DATA_ARRAY_RELU_HPP