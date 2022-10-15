#ifndef NMTOOLS_TESTING_DATA_ARRAY_ATLEAST_3D_HPP
#define NMTOOLS_TESTING_DATA_ARRAY_ATLEAST_3D_HPP

#include "nmtools/array/ndarray.hpp"
#include "nmtools/testing/testing.hpp"

#ifndef NMTOOLS_TESTING_CONSTEXPR

NMTOOLS_TESTING_DECLARE_CASE(array, atleast_3d)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline int a = 1;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline int dim = 3;
        inline int shape[3] = {1,1,1};
        inline int result[1][1][1] = {{{1}}};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        inline int a[1] = {1};
        NMTOOLS_CAST_ARRAYS(a);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        inline int dim = 3;
        inline int shape[3] = {1,1,1};
        inline int result[1][1][1] = {{{1}}};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        inline int a[2][1] = {{1},{2}};
        NMTOOLS_CAST_ARRAYS(a);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        inline int dim = 3;
        inline int shape[3] = {1,2,1};
        inline int result[1][2][1] = {{{1},{2}}};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        inline int a[2][1][2] = {{{1,2}},{{3,4}}};
        NMTOOLS_CAST_ARRAYS(a);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        inline int dim = 3;
        inline int shape[3] = {2,1,2};
        inline int result[2][1][2] = {{{1,2}},{{3,4}}};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        inline int a[2][1][2][1] = {{{{1},{2}}},{{{3},{4}}}};
        NMTOOLS_CAST_ARRAYS(a);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        inline int dim = 4;
        inline int shape[4] = {2,1,2,1};
        inline int result[2][1][2][1] = {{{{1},{2}}},{{{3},{4}}}};
    }
}

#else // (NMTOOLS_TESTING_CONSTEXPR)

NMTOOLS_TESTING_DECLARE_CASE(array, constexpr_atleast_3d)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        constexpr inline int a = 1;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        constexpr inline int dim = 3;
        constexpr inline int shape[3] = {1,1,1};
        constexpr inline int result[1][1][1] = {{{1}}};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        constexpr inline int a[1] = {1};
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(a);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        constexpr inline int dim = 3;
        constexpr inline int shape[3] = {1,1,1};
        constexpr inline int result[1][1][1] = {{{1}}};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        constexpr inline int a[2][1] = {{1},{2}};
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(a);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        constexpr inline int dim = 3;
        constexpr inline int shape[3] = {1,2,1};
        constexpr inline int result[1][2][1] = {{{1},{2}}};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        constexpr inline int a[2][1][2] = {{{1,2}},{{3,4}}};
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(a);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        constexpr inline int dim = 3;
        constexpr inline int shape[3] = {2,1,2};
        constexpr inline int result[2][1][2] = {{{1,2}},{{3,4}}};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        constexpr inline int a[2][1][2][1] = {{{{1},{2}}},{{{3},{4}}}};
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(a);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        constexpr inline int dim = 4;
        constexpr inline int shape[4] = {2,1,2,1};
        constexpr inline int result[2][1][2][1] = {{{{1},{2}}},{{{3},{4}}}};
    }
}

#endif // (NMTOOLS_TESTING_CONSTEXPR)

#endif // NMTOOLS_TESTING_DATA_ARRAY_ATLEAST_3D_HPP