#ifndef NMTOOLS_TESTING_DATA_ARRAY_LDEXP_HPP
#define NMTOOLS_TESTING_DATA_ARRAY_LDEXP_HPP

#include "nmtools/ndarray/dynamic.hpp"
#include "nmtools/ndarray/hybrid.hpp"
#include "nmtools/ndarray/fixed.hpp"
#include "nmtools/testing/doctest.hpp"

#include <vector>
#include <array>
#include <algorithm> // std::ldexp

namespace nm = nmtools;
namespace na = nm::array;
namespace kind = na::kind;

NMTOOLS_TESTING_DECLARE_CASE(view, ldexp)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline int a[3][3] = {
            {0,1,2},
            {3,4,5},
            {6,7,8},
        };
        inline int b[3] = {0,1,2};
        NMTOOLS_CAST_ARRAYS(a)
        NMTOOLS_CAST_ARRAYS(b)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline int shape[2] = {3,3};
        inline float result[3][3] = {
            {std::ldexp(0.f,0.f),std::ldexp(1.f,1.f),std::ldexp(2.f,2.f)},
            {std::ldexp(3.f,0.f),std::ldexp(4.f,1.f),std::ldexp(5.f,2.f)},
            {std::ldexp(6.f,0.f),std::ldexp(7.f,1.f),std::ldexp(8.f,2.f)},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        inline int a[3][3] = {
            {0,1,2},
            {3,4,5},
            {6,7,8},
        };
        inline int b = 2;
        NMTOOLS_CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        inline int shape[2] = {3,3};
        inline float result[3][3] = {
            {std::ldexp(0.f,2.f),std::ldexp(1.f,2.f),std::ldexp(2.f,2.f)},
            {std::ldexp(3.f,2.f),std::ldexp(4.f,2.f),std::ldexp(5.f,2.f)},
            {std::ldexp(6.f,2.f),std::ldexp(7.f,2.f),std::ldexp(8.f,2.f)},
        };
    }
}

#endif // NMTOOLS_TESTING_DATA_ARRAY_LDEXP_HPP