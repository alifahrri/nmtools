#ifndef NMTOOLS_TESTING_DATA_CONSTEXPR_ATLEAST_2D_HPP
#define NMTOOLS_TESTING_DATA_CONSTEXPR_ATLEAST_2D_HPP

#include "nmtools/array/ndarray.hpp"
#include "nmtools/testing/testing.hpp"

NMTOOLS_TESTING_DECLARE_CASE(array, constexpr_atleast_2d)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        constexpr inline int a = 1;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        constexpr inline int shape[2] = {1,1};
        constexpr inline int result[1][1] = {{1}};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        constexpr inline int a[1] = {1};
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(a);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        constexpr inline int shape[2] = {1,1};
        constexpr inline int result[1][1] = {{1}};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        constexpr inline int a[2][1] = {{1},{2}};
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(a);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        constexpr inline int shape[2] = {2,1};
        constexpr inline int result[2][1] = {{1},{2}};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        constexpr inline int a[2][1][2] = {{{1,2}},{{3,4}}};
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(a);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        constexpr inline int shape[3] = {2,1,2};
        constexpr inline int result[2][1][2] = {{{1,2}},{{3,4}}};
    }
}

#endif // NMTOOLS_TESTING_DATA_CONSTEXPR_ATLEAST_2D_HPP