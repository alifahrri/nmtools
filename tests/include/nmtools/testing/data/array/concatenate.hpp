#ifndef NMTOOLS_TESTING_DATA_ARRAY_CONCATENATE_HPP
#define NMTOOLS_TESTING_DATA_ARRAY_CONCATENATE_HPP

#include "nmtools/array/ndarray/dynamic.hpp"
#include "nmtools/array/ndarray/hybrid.hpp"
#include "nmtools/array/ndarray/fixed.hpp"

#include "nmtools/constants.hpp"
#include "testing/doctest.hpp"

#include <vector>
#include <array>
#include <tuple>

namespace nm = nmtools;
namespace na = nm::array;
namespace kind = na::kind;

NMTOOLS_TESTING_DECLARE_CASE(view, concatenate)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline int lhs[2][2] = {{1,2},{3,4}};
        inline int rhs[1][2] = {{5,6}};
        inline int axis = 0;
        inline auto lhs_a = cast<int>(lhs);
        inline auto rhs_a = cast<int>(rhs);
        inline auto lhs_v = cast(lhs,kind::nested_vec);
        inline auto rhs_v = cast(rhs,kind::nested_vec);
        inline auto lhs_d = cast(lhs,kind::dynamic);
        inline auto rhs_d = cast(rhs,kind::dynamic);
        inline auto lhs_h = cast(lhs,kind::hybrid);
        inline auto rhs_h = cast(rhs,kind::hybrid);
        inline auto lhs_f = cast(lhs,kind::fixed);
        inline auto rhs_f = cast(rhs,kind::fixed);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline int shape[2] = {3,2};
        inline int expected[3][2] = {
            {1,2},
            {3,4},
            {5,6},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        inline int lhs[2][2] = {{1,2},{3,4}};
        inline int rhs[2][1] = {{5},{6}};
        inline int axis = 1;
        inline auto lhs_a = cast<int>(lhs);
        inline auto rhs_a = cast<int>(rhs);
        inline auto lhs_v = cast(lhs,kind::nested_vec);
        inline auto rhs_v = cast(rhs,kind::nested_vec);
        inline auto lhs_d = cast(lhs,kind::dynamic);
        inline auto rhs_d = cast(rhs,kind::dynamic);
        inline auto lhs_h = cast(lhs,kind::hybrid);
        inline auto rhs_h = cast(rhs,kind::hybrid);
        inline auto lhs_f = cast(lhs,kind::fixed);
        inline auto rhs_f = cast(rhs,kind::fixed);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        inline int shape[2] = {2,3};
        inline int expected[2][3] = {
            {1,2,5},
            {3,4,6},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        inline int lhs[2][2] = {{1,2},{3,4}};
        inline int rhs[2][1] = {{5},{6}};
        inline auto axis = None;
        inline auto lhs_a = cast<int>(lhs);
        inline auto rhs_a = cast<int>(rhs);
        inline auto lhs_v = cast(lhs,kind::nested_vec);
        inline auto rhs_v = cast(rhs,kind::nested_vec);
        inline auto lhs_d = cast(lhs,kind::dynamic);
        inline auto rhs_d = cast(rhs,kind::dynamic);
        inline auto lhs_h = cast(lhs,kind::hybrid);
        inline auto rhs_h = cast(rhs,kind::hybrid);
        inline auto lhs_f = cast(lhs,kind::fixed);
        inline auto rhs_f = cast(rhs,kind::fixed);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        inline int shape[1] = {6};
        inline int expected[6] = {1,2,3,4,5,6};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        inline int lhs[2][1][2] = {{{1,2}},{{3,4}}};
        inline int rhs[2][1][1] = {{{5}},{{6}}};
        inline int axis = 2;
        inline auto lhs_a = cast<int>(lhs);
        inline auto rhs_a = cast<int>(rhs);
        inline auto lhs_v = cast(lhs,kind::nested_vec);
        inline auto rhs_v = cast(rhs,kind::nested_vec);
        inline auto lhs_d = cast(lhs,kind::dynamic);
        inline auto rhs_d = cast(rhs,kind::dynamic);
        inline auto lhs_h = cast(lhs,kind::hybrid);
        inline auto rhs_h = cast(rhs,kind::hybrid);
        inline auto lhs_f = cast(lhs,kind::fixed);
        inline auto rhs_f = cast(rhs,kind::fixed);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        inline int shape[3] = {2,1,3};
        inline int expected[2][1][3] = {
            {
                {1,2,5}
            },
            {
                {3,4,6},
            }
        };
    }
}

#endif // NMTOOLS_TESTING_DATA_ARRAY_CONCATENATE_HPP