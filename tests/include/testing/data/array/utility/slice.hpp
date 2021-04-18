#ifndef NMTOOLS_TESTING_DATA_ARRAY_UTILITY_SLICE_HPP
#define NMTOOLS_TESTING_DATA_ARRAY_UTILITY_SLICE_HPP

/* TODO: use __has_include */
#include "nmtools/array/fixed.hpp"
#include "nmtools/array/utility.hpp" // nmtools::end_t, make_slice_index
#include "testing/testing.hpp"
#include <array>
#include <tuple>

/* @todo: make simple script to autogenereate test data */

NMTOOLS_TESTING_DECLARE_CASE(slice)
{
    namespace magic = common_matrix::magic;

    template <typename T>
    constexpr T x3[3] = {1,2,3};
    template <typename T>
    constexpr T x5[5] = {1,2,3,4,5};
    template <typename T>
    constexpr T x7[7] = {1,2,3,4,5,6,7};
    template <typename T>
    constexpr T x8[8] = {1,2,3,4,5,6,7,8};
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        NMTOOLS_TESTING_DATA_DECLARE_ARRAY(x,x3);
        NMTOOLS_TESTING_DATA_DECLARE_VEC(x,3);
        inline constexpr size_t start = 1;
        inline constexpr size_t stop = 2;
        using start_t = decltype(make_slice_index<start>());
        using stop_t  = decltype(make_slice_index<stop>());
        NMTOOLS_TESTING_DATA_DECLARE_INTEGER(start);
        NMTOOLS_TESTING_DATA_DECLARE_INTEGER(stop);
        inline constexpr size_t end = 2;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1) {
        inline constexpr auto x = std::array<double,1>{2};
        inline constexpr auto res = std::array<double,1>{2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2) {
        NMTOOLS_TESTING_DATA_DECLARE_ARRAY(x,x5);
        NMTOOLS_TESTING_DATA_DECLARE_VEC(x,5);
        inline constexpr size_t start = 1;
        inline constexpr size_t stop = 4;
        using start_t = decltype(make_slice_index<start>());
        using stop_t  = decltype(make_slice_index<stop>());
        NMTOOLS_TESTING_DATA_DECLARE_INTEGER(start);
        NMTOOLS_TESTING_DATA_DECLARE_INTEGER(stop);
        inline constexpr size_t end = 4;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2) {
        inline constexpr auto x = std::array<double,3>{2,3,4};
        inline constexpr auto res = std::array<double,3>{2,3,4};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3) {
        NMTOOLS_TESTING_DATA_DECLARE_ARRAY(x,x7);
        NMTOOLS_TESTING_DATA_DECLARE_VEC(x,7);
        inline constexpr size_t start = 3;
        inline constexpr size_t stop = 6;
        using start_t = decltype(make_slice_index<start>());
        using stop_t  = decltype(make_slice_index<stop>());
        NMTOOLS_TESTING_DATA_DECLARE_INTEGER(start);
        NMTOOLS_TESTING_DATA_DECLARE_INTEGER(stop);
        inline constexpr size_t end = 6;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3) {
        inline constexpr auto x = std::array<double,3>{4,5,6};
        inline constexpr auto res = std::array<double,3>{4,5,6};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4) {
        // allow testing raw array
        using magic::m5x5;
        NMTOOLS_TESTING_DATA_DECLARE_ARRAY(x,m5x5);
        NMTOOLS_TESTING_DATA_DECLARE_MAT(x,5,5);
        constexpr inline auto row_start = 0;
        constexpr inline auto col_start = 2;
        constexpr inline auto row_stop  = 2;
        constexpr inline auto col_stop  = 5;
        constexpr inline auto start = std::make_tuple(row_start,col_start);
        constexpr inline auto stop  = std::make_tuple(row_stop,col_stop);
        // pack start/stop indices as type to be passed as tparam to slice
        constexpr inline auto start_indices = make_slice_index<row_start,col_start>();
        constexpr inline auto stop_indices  = make_slice_index<row_stop,col_stop>();
        using start_indices_t = decltype(start_indices);
        using stop_indices_t  = decltype(stop_indices);
        // note: DECLARE_INTEGER can also be used for tuple
        NMTOOLS_TESTING_DATA_DECLARE_INTEGER(start);
        NMTOOLS_TESTING_DATA_DECLARE_INTEGER(stop);
        NMTOOLS_TESTING_DATA_DECLARE_INTEGER(row_start);
        NMTOOLS_TESTING_DATA_DECLARE_INTEGER(row_stop);
        NMTOOLS_TESTING_DATA_DECLARE_INTEGER(col_start);
        NMTOOLS_TESTING_DATA_DECLARE_INTEGER(col_stop);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4) {
        /**
         * @brief `octave:> magic(5)(1:2,3:5)`
         * 
         */
        constexpr inline auto res = std::array<std::array<double,3>,2>{{
            {1,    8,   15},
            {7,   14,   16},
        }};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5) {
        // allow testing raw array
        using magic::m10x10;
        NMTOOLS_TESTING_DATA_DECLARE_ARRAY(x,m10x10);
        NMTOOLS_TESTING_DATA_DECLARE_MAT(x,10,10);
        constexpr inline auto row_start = 0;
        constexpr inline auto col_start = 2;
        constexpr inline auto row_stop  = 2;
        constexpr inline auto col_stop  = 5;
        constexpr inline auto start = std::make_tuple(row_start,col_start);
        constexpr inline auto stop  = std::make_tuple(row_stop,col_stop);
        // pack start/stop indices as type to be passed as tparam to slice
        constexpr inline auto start_indices = make_slice_index<row_start,col_start>();
        constexpr inline auto stop_indices  = make_slice_index<row_stop,col_stop>();
        using start_indices_t = decltype(start_indices);
        using stop_indices_t  = decltype(stop_indices);
        // note: DECLARE_INTEGER can also be used for tuple
        NMTOOLS_TESTING_DATA_DECLARE_INTEGER(start);
        NMTOOLS_TESTING_DATA_DECLARE_INTEGER(stop);
        NMTOOLS_TESTING_DATA_DECLARE_INTEGER(row_start);
        NMTOOLS_TESTING_DATA_DECLARE_INTEGER(row_stop);
        NMTOOLS_TESTING_DATA_DECLARE_INTEGER(col_start);
        NMTOOLS_TESTING_DATA_DECLARE_INTEGER(col_stop);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5) {
        /**
         * @brief `octave:> magic(10)(1:2,3:5)`
         * 
         */
        constexpr inline auto res = std::array<std::array<double,3>,2>{{
            {1,    8,   15},
            {7,   14,   16},
        }};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case6) {
        // allow testing raw array
        using magic::m15x15;
        NMTOOLS_TESTING_DATA_DECLARE_ARRAY(x,m15x15);
        NMTOOLS_TESTING_DATA_DECLARE_MAT(x,15,15);
        constexpr inline auto row_start = 0;
        constexpr inline auto col_start = 2;
        constexpr inline auto row_stop  = 2;
        constexpr inline auto col_stop  = 5;
        constexpr inline auto start = std::make_tuple(row_start,col_start);
        constexpr inline auto stop  = std::make_tuple(row_stop,col_stop);
        // pack start/stop indices as type to be passed as tparam to slice
        constexpr inline auto start_indices = make_slice_index<row_start,col_start>();
        constexpr inline auto stop_indices  = make_slice_index<row_stop,col_stop>();
        using start_indices_t = decltype(start_indices);
        using stop_indices_t  = decltype(stop_indices);
        // note: DECLARE_INTEGER can also be used for tuple
        NMTOOLS_TESTING_DATA_DECLARE_INTEGER(start);
        NMTOOLS_TESTING_DATA_DECLARE_INTEGER(stop);
        NMTOOLS_TESTING_DATA_DECLARE_INTEGER(row_start);
        NMTOOLS_TESTING_DATA_DECLARE_INTEGER(row_stop);
        NMTOOLS_TESTING_DATA_DECLARE_INTEGER(col_start);
        NMTOOLS_TESTING_DATA_DECLARE_INTEGER(col_stop);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case6) {
        /**
         * @brief `octave:> magic(15)(1:2,3:5)`
         * 
         */
        constexpr inline auto res = std::array<std::array<double,3>,2>{{
            {156,   173,   190},
            {172,   189,   206},
        }};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case7) {
        // allow testing raw array
        using magic::m20x20;
        NMTOOLS_TESTING_DATA_DECLARE_ARRAY(x,m20x20);
        NMTOOLS_TESTING_DATA_DECLARE_MAT(x,20,20);
        constexpr inline auto row_start = 0;
        constexpr inline auto col_start = 2;
        constexpr inline auto row_stop  = 2;
        constexpr inline auto col_stop  = 5;
        constexpr inline auto start = std::make_tuple(row_start,col_start);
        constexpr inline auto stop  = std::make_tuple(row_stop,col_stop);
        // pack start/stop indices as type to be passed as tparam to slice
        constexpr inline auto start_indices = make_slice_index<row_start,col_start>();
        constexpr inline auto stop_indices  = make_slice_index<row_stop,col_stop>();
        using start_indices_t = decltype(start_indices);
        using stop_indices_t  = decltype(stop_indices);
        // note: DECLARE_INTEGER can also be used for tuple
        NMTOOLS_TESTING_DATA_DECLARE_INTEGER(start);
        NMTOOLS_TESTING_DATA_DECLARE_INTEGER(stop);
        NMTOOLS_TESTING_DATA_DECLARE_INTEGER(row_start);
        NMTOOLS_TESTING_DATA_DECLARE_INTEGER(row_stop);
        NMTOOLS_TESTING_DATA_DECLARE_INTEGER(col_start);
        NMTOOLS_TESTING_DATA_DECLARE_INTEGER(col_stop);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case7) {
        /**
         * @brief `octave:> magic(20)(1:2,3:5)`
         * 
         */
        constexpr inline auto res = std::array<std::array<double,3>,2>{{
            {  3,   397,   396},
            {378,    24,    25},
        }};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case8) {
        // allow testing raw array
        using magic::m25x25;
        NMTOOLS_TESTING_DATA_DECLARE_ARRAY(x,m25x25);
        NMTOOLS_TESTING_DATA_DECLARE_MAT(x,25,25);
        constexpr inline auto row_start = 0;
        constexpr inline auto col_start = 2;
        constexpr inline auto row_stop  = 2;
        constexpr inline auto col_stop  = 5;
        constexpr inline auto start = std::make_tuple(row_start,col_start);
        constexpr inline auto stop  = std::make_tuple(row_stop,col_stop);
        // pack start/stop indices as type to be passed as tparam to slice
        constexpr inline auto start_indices = make_slice_index<row_start,col_start>();
        constexpr inline auto stop_indices  = make_slice_index<row_stop,col_stop>();
        using start_indices_t = decltype(start_indices);
        using stop_indices_t  = decltype(stop_indices);
        // note: DECLARE_INTEGER can also be used for tuple
        NMTOOLS_TESTING_DATA_DECLARE_INTEGER(start);
        NMTOOLS_TESTING_DATA_DECLARE_INTEGER(stop);
        NMTOOLS_TESTING_DATA_DECLARE_INTEGER(row_start);
        NMTOOLS_TESTING_DATA_DECLARE_INTEGER(row_stop);
        NMTOOLS_TESTING_DATA_DECLARE_INTEGER(col_start);
        NMTOOLS_TESTING_DATA_DECLARE_INTEGER(col_stop);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case8) {
        /**
         * @brief `octave:> magic(25)(1:2,3:5)`
         * 
         */
        constexpr inline auto res = std::array<std::array<double,3>,2>{{
            {381,   408,   435},
            {407,   434,   461},
        }};
    }

    using nmtools::end_t;

    NMTOOLS_TESTING_DECLARE_ARGS(case9) {
        // allow testing raw array
        using magic::m5x5;
        NMTOOLS_TESTING_DATA_DECLARE_ARRAY(x,m5x5);
        NMTOOLS_TESTING_DATA_DECLARE_MAT(x,5,5);
        constexpr inline auto row_start = 0;
        constexpr inline auto col_start = 2;
        constexpr inline auto row_stop  = 2;
        constexpr inline auto col_stop  = end_t{};
        constexpr inline auto start = std::make_tuple(row_start,col_start);
        constexpr inline auto stop  = std::make_tuple(row_stop,col_stop);
        // pack start/stop indices as type to be passed as tparam to slice
        constexpr inline auto start_indices = make_slice_index<row_start,col_start>();
        constexpr inline auto stop_indices  = make_slice_index<row_stop,end_t>();
        using start_indices_t = decltype(start_indices);
        using stop_indices_t  = decltype(stop_indices);
        // note: DECLARE_INTEGER can also be used for tuple
        NMTOOLS_TESTING_DATA_DECLARE_INTEGER(start);
        NMTOOLS_TESTING_DATA_DECLARE_INTEGER(stop);
        NMTOOLS_TESTING_DATA_DECLARE_INTEGER(row_start);
        NMTOOLS_TESTING_DATA_DECLARE_INTEGER(row_stop);
        NMTOOLS_TESTING_DATA_DECLARE_INTEGER(col_start);
        NMTOOLS_TESTING_DATA_DECLARE_INTEGER(col_stop);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case9) {
        /**
         * @brief `octave:> magic(5)(1:2,3:5)`
         * 
         */
        constexpr inline auto res = std::array<std::array<double,3>,2>{{
            {1,    8,   15},
            {7,   14,   16},
        }};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case10) {
        // allow testing raw array
        using magic::m10x10;
        NMTOOLS_TESTING_DATA_DECLARE_ARRAY(x,m10x10);
        NMTOOLS_TESTING_DATA_DECLARE_MAT(x,10,10);
        constexpr inline auto row_start = 0;
        constexpr inline auto col_start = 2;
        constexpr inline auto row_stop  = 2;
        constexpr inline auto col_stop  = end_t{};
        constexpr inline auto start = std::make_tuple(row_start,col_start);
        constexpr inline auto stop  = std::make_tuple(row_stop,col_stop);
        // pack start/stop indices as type to be passed as tparam to slice
        constexpr inline auto start_indices = make_slice_index<row_start,col_start>();
        constexpr inline auto stop_indices  = make_slice_index<row_stop,end_t>();
        using start_indices_t = decltype(start_indices);
        using stop_indices_t  = decltype(stop_indices);
        // note: DECLARE_INTEGER can also be used for tuple
        NMTOOLS_TESTING_DATA_DECLARE_INTEGER(start);
        NMTOOLS_TESTING_DATA_DECLARE_INTEGER(stop);
        NMTOOLS_TESTING_DATA_DECLARE_INTEGER(row_start);
        NMTOOLS_TESTING_DATA_DECLARE_INTEGER(row_stop);
        NMTOOLS_TESTING_DATA_DECLARE_INTEGER(col_start);
        NMTOOLS_TESTING_DATA_DECLARE_INTEGER(col_stop);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case10) {
        /**
         * @brief `octave:> magic(10)(1:2,3:5)`
         * 
         */
        constexpr inline auto res = std::array<std::array<double,8>,2>{{
            {1,    8,   15,   67,   74,   51,   58,   40},
            {7,   14,   16,   73,   55,   57,   64,   41},
        }};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case11) {
        // allow testing raw array
        using magic::m15x15;
        NMTOOLS_TESTING_DATA_DECLARE_ARRAY(x,m15x15);
        NMTOOLS_TESTING_DATA_DECLARE_MAT(x,15,15);
        constexpr inline auto row_start = 0;
        constexpr inline auto col_start = 2;
        constexpr inline auto row_stop  = 2;
        constexpr inline auto col_stop  = end_t{};
        constexpr inline auto start = std::make_tuple(row_start,col_start);
        constexpr inline auto stop  = std::make_tuple(row_stop,col_stop);
        // pack start/stop indices as type to be passed as tparam to slice
        constexpr inline auto start_indices = make_slice_index<row_start,col_start>();
        constexpr inline auto stop_indices  = make_slice_index<row_stop,end_t>();
        using start_indices_t = decltype(start_indices);
        using stop_indices_t  = decltype(stop_indices);
        // note: DECLARE_INTEGER can also be used for tuple
        NMTOOLS_TESTING_DATA_DECLARE_INTEGER(start);
        NMTOOLS_TESTING_DATA_DECLARE_INTEGER(stop);
        NMTOOLS_TESTING_DATA_DECLARE_INTEGER(row_start);
        NMTOOLS_TESTING_DATA_DECLARE_INTEGER(row_stop);
        NMTOOLS_TESTING_DATA_DECLARE_INTEGER(col_start);
        NMTOOLS_TESTING_DATA_DECLARE_INTEGER(col_stop);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case11) {
        /**
         * @brief `octave:> magic(15)(1:2,3:5)`
         * 
         */
        constexpr inline auto res = std::array<std::array<double,13>,2>{{
            {156,   173,   190,   207,   224,     1,    18,    35,    52,    69,    86,   103,   120},
            {172,   189,   206,   223,    15,    17,    34,    51,    68,    85,   102,   119,   121},
        }};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case12) {
        // allow testing raw array
        using magic::m20x20;
        NMTOOLS_TESTING_DATA_DECLARE_ARRAY(x,m20x20);
        NMTOOLS_TESTING_DATA_DECLARE_MAT(x,20,20);
        constexpr inline auto row_start = 0;
        constexpr inline auto col_start = 2;
        constexpr inline auto row_stop  = 2;
        constexpr inline auto col_stop  = end_t{};
        constexpr inline auto start = std::make_tuple(row_start,col_start);
        constexpr inline auto stop  = std::make_tuple(row_stop,col_stop);
        // pack start/stop indices as type to be passed as tparam to slice
        constexpr inline auto start_indices = make_slice_index<row_start,col_start>();
        constexpr inline auto stop_indices  = make_slice_index<row_stop,end_t>();
        using start_indices_t = decltype(start_indices);
        using stop_indices_t  = decltype(stop_indices);
        // note: DECLARE_INTEGER can also be used for tuple
        NMTOOLS_TESTING_DATA_DECLARE_INTEGER(start);
        NMTOOLS_TESTING_DATA_DECLARE_INTEGER(stop);
        NMTOOLS_TESTING_DATA_DECLARE_INTEGER(row_start);
        NMTOOLS_TESTING_DATA_DECLARE_INTEGER(row_stop);
        NMTOOLS_TESTING_DATA_DECLARE_INTEGER(col_start);
        NMTOOLS_TESTING_DATA_DECLARE_INTEGER(col_stop);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case12) {
        /**
         * @brief `octave:> magic(20)(1:2,3:5)`
         * 
         */
        constexpr inline auto res = std::array<std::array<double,18>,2>{{
            {  3,   397,   396,     6,     7,   393,   392,    10,    11,   389,   388,    14,    15,   385,   384,    18,    19,   381},
            {378,    24,    25,   375,   374,    28,    29,   371,   370,    32,    33,   367,   366,    36,    37,   363,   362,    40},
        }};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case13) {
        // allow testing raw array
        using magic::m25x25;
        NMTOOLS_TESTING_DATA_DECLARE_ARRAY(x,m25x25);
        NMTOOLS_TESTING_DATA_DECLARE_MAT(x,25,25);
        constexpr inline auto row_start = 0;
        constexpr inline auto col_start = 2;
        constexpr inline auto row_stop  = 2;
        constexpr inline auto col_stop  = end_t{};
        constexpr inline auto start = std::make_tuple(row_start,col_start);
        constexpr inline auto stop  = std::make_tuple(row_stop,col_stop);
        // pack start/stop indices as type to be passed as tparam to slice
        constexpr inline auto start_indices = make_slice_index<row_start,col_start>();
        constexpr inline auto stop_indices  = make_slice_index<row_stop,end_t>();
        using start_indices_t = decltype(start_indices);
        using stop_indices_t  = decltype(stop_indices);
        // note: DECLARE_INTEGER can also be used for tuple
        NMTOOLS_TESTING_DATA_DECLARE_INTEGER(start);
        NMTOOLS_TESTING_DATA_DECLARE_INTEGER(stop);
        NMTOOLS_TESTING_DATA_DECLARE_INTEGER(row_start);
        NMTOOLS_TESTING_DATA_DECLARE_INTEGER(row_stop);
        NMTOOLS_TESTING_DATA_DECLARE_INTEGER(col_start);
        NMTOOLS_TESTING_DATA_DECLARE_INTEGER(col_stop);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case13) {
        /**
         * @brief `octave:> magic(25)(1:2,3:5)`
         * 
         */
        constexpr inline auto res = std::array<std::array<double,23>,2>{{
            {381,   408,   435,   462,   489,   516,   543,   570,   597,   624,     1,    28,    55,    82,   109,   136,   163,   190,   217,   244,   271,   298,   325},
            {407,   434,   461,   488,   515,   542,   569,   596,   623,    25,    27,    54,    81,   108,   135,   162,   189,   216,   243,   270,   297,   324,   326},
        }};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case14) {
        using common::v5;
        NMTOOLS_TESTING_DATA_DECLARE_ARRAY(x,v5);
        NMTOOLS_TESTING_DATA_DECLARE_VEC(x,5);
        constexpr inline auto start = 2;
        constexpr inline auto stop  = end_t{};
        // pack start/stop indices as type to be passed as tparam to slice
        constexpr inline auto start_index = make_slice_index<start>();
        constexpr inline auto stop_index  = make_slice_index<end_t>();
        using start_index_t = decltype(start_index);
        using stop_index_t  = decltype(stop_index);
        // note: DECLARE_INTEGER can also be used for tuple
        NMTOOLS_TESTING_DATA_DECLARE_INTEGER(start);
        NMTOOLS_TESTING_DATA_DECLARE_INTEGER(stop);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case14) {
        constexpr inline auto res = std::array<double,3>{1,    8,   15};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case15) {
        using common::v10;
        NMTOOLS_TESTING_DATA_DECLARE_ARRAY(x,v10);
        NMTOOLS_TESTING_DATA_DECLARE_VEC(x,10);
        constexpr inline auto start = 2;
        constexpr inline auto stop  = end_t{};
        // pack start/stop indices as type to be passed as tparam to slice
        constexpr inline auto start_index = make_slice_index<start>();
        constexpr inline auto stop_index  = make_slice_index<end_t>();
        using start_index_t = decltype(start_index);
        using stop_index_t  = decltype(stop_index);
        // note: DECLARE_INTEGER can also be used for tuple
        NMTOOLS_TESTING_DATA_DECLARE_INTEGER(start);
        NMTOOLS_TESTING_DATA_DECLARE_INTEGER(stop);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case15) {
        constexpr inline auto res = std::array<double,8>{1,    8,   15,   67,   74,   51,   58,   40};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case16) {
        using common::v15;
        NMTOOLS_TESTING_DATA_DECLARE_ARRAY(x,v15);
        NMTOOLS_TESTING_DATA_DECLARE_VEC(x,15);
        constexpr inline auto start = 2;
        constexpr inline auto stop  = end_t{};
        // pack start/stop indices as type to be passed as tparam to slice
        constexpr inline auto start_index = make_slice_index<start>();
        constexpr inline auto stop_index  = make_slice_index<end_t>();
        using start_index_t = decltype(start_index);
        using stop_index_t  = decltype(stop_index);
        // note: DECLARE_INTEGER can also be used for tuple
        NMTOOLS_TESTING_DATA_DECLARE_INTEGER(start);
        NMTOOLS_TESTING_DATA_DECLARE_INTEGER(stop);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case16) {
        constexpr inline auto res = std::array<double,13>{156,   173,   190,   207,   224,     1,    18,    35,    52,    69,    86,   103,   120};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case17) {
        using common::v20;
        NMTOOLS_TESTING_DATA_DECLARE_ARRAY(x,v20);
        NMTOOLS_TESTING_DATA_DECLARE_VEC(x,20);
        constexpr inline auto start = 2;
        constexpr inline auto stop  = end_t{};
        // pack start/stop indices as type to be passed as tparam to slice
        constexpr inline auto start_index = make_slice_index<start>();
        constexpr inline auto stop_index  = make_slice_index<end_t>();
        using start_index_t = decltype(start_index);
        using stop_index_t  = decltype(stop_index);
        // note: DECLARE_INTEGER can also be used for tuple
        NMTOOLS_TESTING_DATA_DECLARE_INTEGER(start);
        NMTOOLS_TESTING_DATA_DECLARE_INTEGER(stop);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case17) {
        constexpr inline auto res = std::array<double,18>{3,   397,   396,     6,     7,   393,   392,    10,    11,   389,   388,    14,    15,   385,   384,    18,    19,   381};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case18) {
        using common::v25;
        NMTOOLS_TESTING_DATA_DECLARE_ARRAY(x,v25);
        NMTOOLS_TESTING_DATA_DECLARE_VEC(x,25);
        constexpr inline auto start = 2;
        constexpr inline auto stop  = end_t{};
        // pack start/stop indices as type to be passed as tparam to slice
        constexpr inline auto start_index = make_slice_index<start>();
        constexpr inline auto stop_index  = make_slice_index<end_t>();
        using start_index_t = decltype(start_index);
        using stop_index_t  = decltype(stop_index);
        // note: DECLARE_INTEGER can also be used for tuple
        NMTOOLS_TESTING_DATA_DECLARE_INTEGER(start);
        NMTOOLS_TESTING_DATA_DECLARE_INTEGER(stop);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case18) {
        constexpr inline auto res = std::array<double,23>{381,   408,   435,   462,   489,   516,   543,   570,   597,   624,     1,    28,    55,    82,   109,   136,   163,   190,   217,   244,   271,   298,   325};
    }
}

#endif // NMTOOLS_TESTING_DATA_ARRAY_UTILITY_SLICE_HPP