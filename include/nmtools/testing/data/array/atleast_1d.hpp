#ifndef NMTOOLS_TESTING_DATA_ARRAY_ATLEAST_1D_HPP
#define NMTOOLS_TESTING_DATA_ARRAY_ATLEAST_1D_HPP

#include "nmtools/ndarray.hpp"
#include "nmtools/testing/testing.hpp"

NMTOOLS_TESTING_DECLARE_CASE(array, atleast_1d)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline int a = 1;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline int result[1] = {1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        inline int a[1] = {1};
        NMTOOLS_CAST_ARRAYS(a);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        inline int result[1] = {1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        inline int a[2][1] = {{1},{2}};
        NMTOOLS_CAST_ARRAYS(a);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        inline int result[2][1] = {{1},{2}};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        inline int a[2][1][2] = {{{1,2}},{{3,4}}};
        NMTOOLS_CAST_ARRAYS(a);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        inline int result[2][1][2] = {{{1,2}},{{3,4}}};
    }
}

#endif // NMTOOLS_TESTING_DATA_ARRAY_ATLEAST_1D_HPP