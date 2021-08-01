#ifndef NMTOOLS_TESTING_DATA_ARRAY_FLATTEN_HPP
#define NMTOOLS_TESTING_DATA_ARRAY_FLATTEN_HPP

#include "nmtools/array/fixed.hpp"
#include "nmtools/array/dynamic.hpp"
#include "nmtools/array/view.hpp"
#include "nmtools/utils/isclose.hpp"
#include "nmtools/utils/isequal.hpp"
#include "testing/doctest.hpp"

#include <array>
#include <vector>

namespace nm = nmtools;
namespace na = nm::array;
namespace view = nm::view;
namespace meta = nm::meta;
namespace kind = na::kind;

NMTOOLS_TESTING_DECLARE_CASE(flatten)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline double array[3] = {1.,2.,3.};
        inline auto array_a = cast<double>(array);
        inline auto array_v = cast(array,kind::nested_vec);
        inline auto array_f = cast(array,kind::fixed);
        inline auto array_d = cast(array,kind::dynamic);
        inline auto array_h = cast(array,kind::hybrid);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline int shape_[1] = {3};
        inline auto shape = cast<int>(shape_);
        inline double expected[3] = {1,2,3};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        inline double array[2][3] = {
            {1.,2.,3.},
            {3.,4.,5.},
        };
        inline auto array_a = cast<double>(array);
        inline auto array_v = cast(array,kind::nested_vec);
        inline auto array_f = cast(array,kind::fixed);
        inline auto array_d = cast(array,kind::dynamic);
        inline auto array_h = cast(array,kind::hybrid);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        inline int shape_[1] = {6};
        inline auto shape = cast<int>(shape_);
        inline double expected[6] = {1,2,3,3,4,5};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        inline double array[2][3][1] = {
            {{1.},{2.},{3.}},
            {{3.},{4.},{5.}},
        };
        inline auto array_a = cast<double>(array);
        inline auto array_v = cast(array,kind::nested_vec);
        inline auto array_f = cast(array,kind::fixed);
        inline auto array_d = cast(array,kind::dynamic);
        inline auto array_h = cast(array,kind::hybrid);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        inline int shape_[1] = {6};
        inline auto shape = cast<int>(shape_);
        inline double expected[6] = {1,2,3,3,4,5};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        inline double array[2][3][2] = {
            {
                {1.,6.},
                {2.,7.},
                {3.,8.}
            },
            {
                {3.,9.},
                {4.,10.},
                {5.,11.}
            },
        };
        inline auto array_a = cast<double>(array);
        inline auto array_v = cast(array,kind::nested_vec);
        inline auto array_f = cast(array,kind::fixed);
        inline auto array_d = cast(array,kind::dynamic);
        inline auto array_h = cast(array,kind::hybrid);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        // isequal doesnt support tuple and raw yet
        inline int shape_[1] = {12};
        inline auto shape = cast<int>(shape_);
        inline double expected[12] = {1,6,2,7,3,8,3,9,4,10,5,11};
    }
}

#endif // NMTOOLS_TESTING_DATA_ARRAY_FLATTEN_HPP