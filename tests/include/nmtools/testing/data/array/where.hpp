#ifndef NMTOOLS_TESTING_DATA_ARRAY_WHERE_HPP
#define NMTOOLS_TESTING_DATA_ARRAY_WHERE_HPP

#include "nmtools/array/view/where.hpp"
#include "nmtools/array/ndarray/dynamic.hpp"
#include "nmtools/array/ndarray/hybrid.hpp"
#include "nmtools/array/ndarray/fixed.hpp"
#include "nmtools/testing/doctest.hpp"

#include <array>
#include <vector>

namespace nm = nmtools;
namespace na = nm::array;
namespace kind = na::kind;

NMTOOLS_TESTING_DECLARE_CASE(view, where)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline bool condition[10] = {true, true, true, true, true, false, false, false, false, false};
        inline int x[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
        inline int y[10] = {0,10,20,30,40,50,60,70,80,90};
        inline auto condition_a = cast<bool>(condition);
        inline auto condition_v = cast(condition, kind::nested_vec);
        inline auto condition_d = cast(condition, kind::dynamic);
        inline auto condition_f = cast(condition, kind::fixed);
        inline auto condition_h = cast(condition, kind::hybrid);
        inline auto x_a = cast<int>(x);
        inline auto x_v = cast(x, kind::nested_vec);
        inline auto x_d = cast(x, kind::dynamic);
        inline auto x_f = cast(x, kind::fixed);
        inline auto x_h = cast(x, kind::hybrid);
        inline auto y_a = cast<int>(y);
        inline auto y_v = cast(y, kind::nested_vec);
        inline auto y_d = cast(y, kind::dynamic);
        inline auto y_f = cast(y, kind::fixed);
        inline auto y_h = cast(y, kind::hybrid);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline int dim = 1;
        inline int shape[1] = {10};
        inline int result[10] = {0, 1, 2, 3, 4, 50, 60, 70, 80, 90};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        inline bool condition[3][4] = {
            {false,  true,  true, true},
            {false, false,  true, true},
            {false, false, false, true},
        };
        inline int x[3][1] = {
            {0},
            {1},
            {2},
        };
        inline int y[1][4] = {{10,11,12,13}};
        inline auto condition_a = cast<bool>(condition);
        inline auto condition_v = cast(condition, kind::nested_vec);
        inline auto condition_d = cast(condition, kind::dynamic);
        inline auto condition_f = cast(condition, kind::fixed);
        inline auto condition_h = cast(condition, kind::hybrid);
        inline auto x_a = cast<int>(x);
        inline auto x_v = cast(x, kind::nested_vec);
        inline auto x_d = cast(x, kind::dynamic);
        inline auto x_f = cast(x, kind::fixed);
        inline auto x_h = cast(x, kind::hybrid);
        inline auto y_a = cast<int>(y);
        inline auto y_v = cast(y, kind::nested_vec);
        inline auto y_d = cast(y, kind::dynamic);
        inline auto y_f = cast(y, kind::fixed);
        inline auto y_h = cast(y, kind::hybrid);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        inline int dim = 2;
        inline int shape[2] = {3,4};
        inline int result[3][4] = {
            {10,  0,  0, 0},
            {10, 11,  1, 1},
            {10, 11, 12, 2},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        inline bool condition[3][4] = {
            {false,  true,  true, true},
            {false, false,  true, true},
            {false, false, false, true},
        };
        inline int x[1][3][1] = {
            {
                {0},
                {1},
                {2},
            }
        };
        inline int y[1][4] = {{10,11,12,13}};
        inline auto condition_a = cast<bool>(condition);
        inline auto condition_v = cast(condition, kind::nested_vec);
        inline auto condition_d = cast(condition, kind::dynamic);
        inline auto condition_f = cast(condition, kind::fixed);
        inline auto condition_h = cast(condition, kind::hybrid);
        inline auto x_a = cast<int>(x);
        inline auto x_v = cast(x, kind::nested_vec);
        inline auto x_d = cast(x, kind::dynamic);
        inline auto x_f = cast(x, kind::fixed);
        inline auto x_h = cast(x, kind::hybrid);
        inline auto y_a = cast<int>(y);
        inline auto y_v = cast(y, kind::nested_vec);
        inline auto y_d = cast(y, kind::dynamic);
        inline auto y_f = cast(y, kind::fixed);
        inline auto y_h = cast(y, kind::hybrid);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        inline int dim = 3;
        inline int shape[3] = {1,3,4};
        inline int result[1][3][4] = {
            {
                {10,  0,  0, 0},
                {10, 11,  1, 1},
                {10, 11, 12, 2},
            }
        };
    }
}

#endif // NMTOOLS_TESTING_DATA_ARRAY_WHERE_HPP