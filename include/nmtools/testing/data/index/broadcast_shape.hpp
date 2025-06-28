#ifndef NMTOOLS_TESTING_DATA_INDEX_BROADCAST_SHAPE_HPP
#define NMTOOLS_TESTING_DATA_INDEX_BROADCAST_SHAPE_HPP

#include "nmtools/testing/doctest.hpp"

namespace nm = nmtools;
namespace na = nmtools;
namespace meta = nm::meta;
namespace kind = na::kind;

NMTOOLS_TESTING_DECLARE_CASE(broadcast_shape)
{
    using namespace literals;

    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        constexpr inline int a[2] = {5,4};
        constexpr inline int b[1] = {1};
        NMTOOLS_CAST_INDEX_ARRAYS(a)
        NMTOOLS_CAST_INDEX_ARRAYS(b)

        inline auto a_ct = nmtools_tuple{5_ct,4_ct};
        inline auto b_ct = nmtools_tuple{1_ct};
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline nm_bool_t success = true;
        inline int expected[2] = {5,4};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        constexpr inline int a[1] = {1};
        constexpr inline int b[2] = {5,4};
        NMTOOLS_CAST_INDEX_ARRAYS(a)
        NMTOOLS_CAST_INDEX_ARRAYS(b)

        inline auto a_ct = nmtools_tuple{1_ct};
        inline auto b_ct = nmtools_tuple{5_ct,4_ct};
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        inline nm_bool_t success = true;
        inline int expected[2] = {5,4};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        constexpr inline int a[1] = {4};
        constexpr inline int b[2] = {5,4};
        NMTOOLS_CAST_INDEX_ARRAYS(a)
        NMTOOLS_CAST_INDEX_ARRAYS(b)

        inline auto a_ct = nmtools_tuple{4_ct};
        inline auto b_ct = nmtools_tuple{5_ct,4_ct};
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        inline nm_bool_t success = true;
        inline int expected[2] = {5,4};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        constexpr inline int a[4] = {8,1,6,1};
        constexpr inline int b[3] = {7,1,5};
        NMTOOLS_CAST_INDEX_ARRAYS(a)
        NMTOOLS_CAST_INDEX_ARRAYS(b)

        inline auto a_ct = nmtools_tuple{8_ct,1_ct,6_ct,1_ct};
        inline auto b_ct = nmtools_tuple{7_ct,1_ct,5_ct};
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        inline nm_bool_t success = true;
        inline int expected[4] = {8,7,6,5};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        constexpr inline int a[3] = {256,256,3};
        constexpr inline int b[1] = {3};
        NMTOOLS_CAST_INDEX_ARRAYS(a)
        NMTOOLS_CAST_INDEX_ARRAYS(b)

        inline auto a_ct = nmtools_tuple{256_ct,256_ct,3_ct};
        inline auto b_ct = nmtools_tuple{3_ct};
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        inline nm_bool_t success = true;
        inline int expected[3] = {256,256,3};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case6)
    {
        constexpr inline int a[1] = {5};
        constexpr inline int b[2] = {5,4};
        NMTOOLS_CAST_INDEX_ARRAYS(a)
        NMTOOLS_CAST_INDEX_ARRAYS(b)

        inline auto a_ct = nmtools_tuple{5_ct};
        inline auto b_ct = nmtools_tuple{5_ct,4_ct};
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case6)
    {
        inline nm_bool_t success = false;
        inline auto expected = meta::Nothing;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case7)
    {
        constexpr inline int a[2] = {2,1};
        constexpr inline int b[3] = {8,4,3};
        NMTOOLS_CAST_INDEX_ARRAYS(a)
        NMTOOLS_CAST_INDEX_ARRAYS(b)

        inline auto a_ct = nmtools_tuple{2_ct,1_ct};
        inline auto b_ct = nmtools_tuple{8_ct,4_ct,3_ct};
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case7)
    {
        inline nm_bool_t success = false;
        inline auto expected = meta::Nothing;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case8)
    {
        constexpr inline int a[2] = {4,1};
        constexpr inline int b[3] = {8,1,3};
        constexpr inline int c[1] = {3};
        NMTOOLS_CAST_INDEX_ARRAYS(a)
        NMTOOLS_CAST_INDEX_ARRAYS(b)
        NMTOOLS_CAST_INDEX_ARRAYS(c)

        inline auto a_ct = nmtools_tuple{4_ct,1_ct};
        inline auto b_ct = nmtools_tuple{8_ct,1_ct,3_ct};
        inline auto c_ct = nmtools_tuple{3_ct};
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case8)
    {
        inline nm_bool_t success = true;
        inline int expected[3] = {8,4,3};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case9)
    {
        constexpr inline int a[2] = {4,1};
        constexpr inline int b[3] = {8,2,3};
        constexpr inline int c[1] = {3};
        NMTOOLS_CAST_INDEX_ARRAYS(a)
        NMTOOLS_CAST_INDEX_ARRAYS(b)
        NMTOOLS_CAST_INDEX_ARRAYS(c)

        inline auto a_ct = nmtools_tuple{4_ct,1_ct};
        inline auto b_ct = nmtools_tuple{8_ct,2_ct,3_ct};
        inline auto c_ct = nmtools_tuple{3_ct};
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case9)
    {
        inline nm_bool_t success = false;
        inline auto expected = meta::Nothing;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case10)
    {
        constexpr inline int a[2] = {4,1};
        constexpr inline int b[3] = {8,1,3};
        constexpr inline int c[1] = {3};
        constexpr inline int d[6] = {2,2,3,1,4,1};
        NMTOOLS_CAST_INDEX_ARRAYS(a)
        NMTOOLS_CAST_INDEX_ARRAYS(b)
        NMTOOLS_CAST_INDEX_ARRAYS(c)
        NMTOOLS_CAST_INDEX_ARRAYS(d)

        inline auto a_ct = nmtools_tuple{4_ct,1_ct};
        inline auto b_ct = nmtools_tuple{8_ct,1_ct,3_ct};
        inline auto c_ct = nmtools_tuple{3_ct};
        inline auto d_ct = nmtools_tuple{2_ct,2_ct,3_ct,1_ct,4_ct,1_ct};
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case10)
    {
        inline nm_bool_t success = true;
        inline int expected[6] = {2,2,3,8,4,3};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case11)
    {
        constexpr inline int a[2] =         {4,1};
        constexpr inline int b[3] =       {8,1,3};
        constexpr inline int c[1] =           {3};
        constexpr inline int d[6] = {2,2,3,1,4,1};
        constexpr inline int e[1] =           {1};
        constexpr inline int f[4] =     {3,1,4,1};
        constexpr inline int g[6] = {2,1,1,1,1,1};
        NMTOOLS_CAST_INDEX_ARRAYS(a)
        NMTOOLS_CAST_INDEX_ARRAYS(b)
        NMTOOLS_CAST_INDEX_ARRAYS(c)
        NMTOOLS_CAST_INDEX_ARRAYS(d)
        NMTOOLS_CAST_INDEX_ARRAYS(e)
        NMTOOLS_CAST_INDEX_ARRAYS(f)
        NMTOOLS_CAST_INDEX_ARRAYS(g)

        inline auto a_ct = nmtools_tuple{4_ct,1_ct};
        inline auto b_ct = nmtools_tuple{8_ct,1_ct,3_ct};
        inline auto c_ct = nmtools_tuple{3_ct};
        inline auto d_ct = nmtools_tuple{2_ct,2_ct,3_ct,1_ct,4_ct,1_ct};
        inline auto e_ct = nmtools_tuple{1_ct};
        inline auto f_ct = nmtools_tuple{3_ct,1_ct,4_ct,1_ct};
        inline auto g_ct = nmtools_tuple{2_ct,1_ct,1_ct,1_ct,1_ct,1_ct};
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case11)
    {
        inline nm_bool_t success = true;
        inline int expected[6] = {2,2,3,8,4,3};
    }
}

#endif // NMTOOLS_TESTING_DATA_INDEX_BROADCAST_SHAPE_HPP