#ifndef NMTOOLS_TESTING_DATA_ARRAY_RESHAPE_HPP
#define NMTOOLS_TESTING_DATA_ARRAY_RESHAPE_HPP

#include "nmtools/constants.hpp"
#include "nmtools/array/fixed.hpp"
#include "nmtools/array/dynamic.hpp"
#include "nmtools/array/index/as_tuple.hpp"
#include "testing/doctest.hpp"

#include <array>
#include <tuple>
#include <vector>

namespace nm = nmtools;
namespace na = nm::array;
namespace view = nm::view;
namespace meta = nm::meta;
namespace kind = na::kind;
using namespace nm::literals;

#define CAST_ARRAYS(name) \
inline auto name##_a = cast(name, kind::nested_arr); \
inline auto name##_v = cast(name, kind::nested_vec); \
inline auto name##_f = cast(name, kind::fixed); \
inline auto name##_d = cast(name, kind::dynamic); \
inline auto name##_h = cast(name, kind::hybrid); \

NMTOOLS_TESTING_DECLARE_CASE(reshape)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline double array[12] = {1,2,3,4,5,6,7,8,9,10,11,12};
        CAST_ARRAYS(array)
        inline int newshape[2] = {12,1};
        inline auto newshape_ct = std::tuple{12_ct, 1_ct};
        inline auto newshape_a = cast<int>(newshape);
        inline auto newshape_v = cast(newshape,kind::nested_vec);
        inline auto newshape_t = index::as_tuple(newshape_a);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        // isclose doesnt support tuple and raw yet
        inline int shape_[2] = {12,1};
        inline auto shape = cast<int>(shape_);
        inline double expected[12][1] = {
            {1.}, {2.}, {3.}, {4.}, {5.}, {6.}, {7.}, {8.}, {9.}, {10.}, {11.}, {12.}
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        inline double array[12] = {1,2,3,4,5,6,7,8,9,10,11,12};
        CAST_ARRAYS(array)
        inline int newshape[2] = {3,4};
        inline auto newshape_ct = std::tuple{3_ct, 4_ct};
        inline auto newshape_a = cast<int>(newshape);
        inline auto newshape_v = cast(newshape,kind::nested_vec);
        inline auto newshape_t = index::as_tuple(newshape_a);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        // isclose doesn support tuple and raw yet
        inline int shape_[2] = {3,4};
        inline auto shape = cast<int>(shape_);
        inline double expected[3][4] = {
            {1.,  2.,  3.,  4.},
            {5.,  6.,  7.,  8.},
            {9., 10., 11., 12.}
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        inline double array[12] = {1,2,3,4,5,6,7,8,9,10,11,12};
        CAST_ARRAYS(array)
        inline int newshape[4] = {1,2,3,2};
        inline auto newshape_ct = std::tuple{1_ct, 2_ct, 3_ct, 2_ct};
        inline auto newshape_a = cast<int>(newshape);
        inline auto newshape_v = cast(newshape,kind::nested_vec);
        inline auto newshape_t = index::as_tuple(newshape_a);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        // isclose doesn support tuple and raw yet
        inline int shape_[4] = {1,2,3,2};
        inline auto shape = cast<int>(shape_);
        inline double expected[1][2][3][2] = {
            {
                {
                    {1., 2.},
                    {3., 4.},
                    {5., 6.}
                },
                {
                    {7.,  8.},
                    {9., 10.},
                    {11.,12.}
                }
            }
        };
    }
}

#undef CAST_ARRAYS

#endif // NMTOOLS_TESTING_DATA_ARRAY_RESHAPE_HPP