#ifndef NMTOOLS_TESTING_DATA_ARRAY_CONCATENATE_HPP
#define NMTOOLS_TESTING_DATA_ARRAY_CONCATENATE_HPP

#include "nmtools/testing/testing.hpp"
#include "nmtools/testing/array_cast.hpp"

namespace nm = nmtools;
namespace na = nmtools;
namespace kind = na::kind;

NMTOOLS_TESTING_DECLARE_CASE(view, concatenate)
{
    using namespace nmtools::literals;

#ifndef NMTOOLS_TESTING_MINIMIZE_FOOTPRINT
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline int8_t lhs[2][2] = {{1,2},{3,4}};
        inline int8_t rhs[1][2] = {{5,6}};
        inline int8_t axis = 0;
        NMTOOLS_CAST_ARRAYS(lhs);
        NMTOOLS_CAST_ARRAYS(rhs);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline int8_t shape[2] = {3,2};
        inline int8_t expected[3][2] = {
            {1,2},
            {3,4},
            {5,6},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        inline int8_t lhs[2][2] = {{1,2},{3,4}};
        inline int8_t rhs[2][1] = {{5},{6}};
        inline int8_t axis = 1;
        NMTOOLS_CAST_ARRAYS(lhs);
        NMTOOLS_CAST_ARRAYS(rhs);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        inline int8_t shape[2] = {2,3};
        inline int8_t expected[2][3] = {
            {1,2,5},
            {3,4,6},
        };
    }
#endif // NMTOOLS_TESTING_MINIMIZE_FOOTPRINT

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        inline int8_t lhs[2][2] = {{1,2},{3,4}};
        inline int8_t rhs[2][1] = {{5},{6}};
        inline auto axis = None;
        NMTOOLS_CAST_ARRAYS(lhs);
        NMTOOLS_CAST_ARRAYS(rhs);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        inline int8_t shape[1] = {6};
        inline int8_t expected[6] = {1,2,3,4,5,6};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        inline int8_t lhs[2][1][2] = {{{1,2}},{{3,4}}};
        inline int8_t rhs[2][1][1] = {{{5}},{{6}}};
        inline int8_t axis = 2;
        inline auto axis_ct = 2_ct;
        NMTOOLS_CAST_ARRAYS(lhs);
        NMTOOLS_CAST_ARRAYS(rhs);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        inline int8_t shape[3] = {2,1,3};
        inline int8_t expected[2][1][3] = {
            {
                {1,2,5}
            },
            {
                {3,4,6},
            }
        };
    }
}

NMTOOLS_TESTING_DECLARE_CASE(array, constexpr_concatenate)
{
    using namespace nmtools::literals;

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        constexpr inline int8_t lhs[2][2] = {{1,2},{3,4}};
        constexpr inline int8_t rhs[2][1] = {{5},{6}};
        constexpr inline auto axis = None;
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(lhs);
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(rhs);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        constexpr inline int8_t shape[1] = {6};
        constexpr inline int8_t expected[6] = {1,2,3,4,5,6};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        constexpr inline int8_t lhs[2][1][2] = {{{1,2}},{{3,4}}};
        constexpr inline int8_t rhs[2][1][1] = {{{5}},{{6}}};
        constexpr inline int8_t axis = 2;
        constexpr inline auto axis_ct = 2_ct;
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(lhs);
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(rhs);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        constexpr inline int8_t shape[3] = {2,1,3};
        constexpr inline int8_t expected[2][1][3] = {
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