#ifndef NMTOOLS_TESTING_DATA_INDEX_FREE_AXES_HPP
#define NMTOOLS_TESTING_DATA_INDEX_FREE_AXES_HPP

#include "nmtools/testing/doctest.hpp"

using namespace nmtools::literals;

NMTOOLS_TESTING_DECLARE_CASE(free_axes)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline int a[2] = {5,4};
        inline int b[1] = {1};
        NMTOOLS_CAST_INDEX_ARRAYS(a)
        NMTOOLS_CAST_INDEX_ARRAYS(b)
        NMTOOLS_MAYBE_CAST_INDEX_ARRAYS(a)
        NMTOOLS_MAYBE_CAST_INDEX_ARRAYS(b)
        inline auto a_ct = nmtools_tuple{5_ct,4_ct};
        inline auto b_ct = nmtools_tuple{1_ct};
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline bool x[2] = {true, true};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        inline int a[2] = {5,4};
        inline int b[1] = {4};
        NMTOOLS_CAST_INDEX_ARRAYS(a)
        NMTOOLS_CAST_INDEX_ARRAYS(b)
        NMTOOLS_MAYBE_CAST_INDEX_ARRAYS(a)
        NMTOOLS_MAYBE_CAST_INDEX_ARRAYS(b)
        inline auto a_ct = nmtools_tuple{5_ct,4_ct};
        inline auto b_ct = nmtools_tuple{4_ct};
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        inline bool x[2] = {true, false};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        inline int a[4] = {8,7,6,5};
        inline int b[3] = {7,1,5};
        NMTOOLS_CAST_INDEX_ARRAYS(a)
        NMTOOLS_CAST_INDEX_ARRAYS(b)
        NMTOOLS_MAYBE_CAST_INDEX_ARRAYS(a)
        NMTOOLS_MAYBE_CAST_INDEX_ARRAYS(b)
        inline auto a_ct = nmtools_tuple{8_ct,7_ct,6_ct,5_ct};
        inline auto b_ct = nmtools_tuple{7_ct,1_ct,5_ct};
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        inline bool x[4] = {true, false, true, false};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        inline int a[4] = {8,7,6,5};
        inline int b[4] = {8,1,5,1};
        NMTOOLS_CAST_INDEX_ARRAYS(a)
        NMTOOLS_CAST_INDEX_ARRAYS(b)
        NMTOOLS_MAYBE_CAST_INDEX_ARRAYS(a)
        NMTOOLS_MAYBE_CAST_INDEX_ARRAYS(b)
        inline auto a_ct = nmtools_tuple{8_ct,7_ct,6_ct,5_ct};
        inline auto b_ct = nmtools_tuple{8_ct,1_ct,5_ct,1_ct};
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        inline bool x[4] = {false, true, false, true};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        inline int a[3] = {256,256,3};
        inline int b[1] = {3};
        NMTOOLS_CAST_INDEX_ARRAYS(a)
        NMTOOLS_CAST_INDEX_ARRAYS(b)
        NMTOOLS_MAYBE_CAST_INDEX_ARRAYS(a)
        NMTOOLS_MAYBE_CAST_INDEX_ARRAYS(b)
        inline auto a_ct = nmtools_tuple{256_ct,256_ct,3_ct};
        inline auto b_ct = nmtools_tuple{3_ct};
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        inline bool x[3] = {true, true, false};
    }
}

#endif // NMTOOLS_TESTING_DATA_INDEX_FREE_AXES_HPP