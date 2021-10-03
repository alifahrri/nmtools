#ifndef NMTOOLS_TESTING_DATA_ARRAY_TILE_HPP
#define NMTOOLS_TESTING_DATA_ARRAY_TILE_HPP

#include "nmtools/array/view/tile.hpp"
#include "nmtools/array/ndarray/dynamic.hpp"
#include "nmtools/array/ndarray/hybrid.hpp"
#include "nmtools/array/ndarray/fixed.hpp"

#include "nmtools/testing/testing.hpp"

#include <vector>
#include <array>
#include <tuple>

namespace nm = nmtools;
namespace na = nm::array;
namespace kind = na::kind;

NMTOOLS_TESTING_DECLARE_CASE(view, tile)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline int array[2][1][4] = {
            {
                {0,1,2,3},
            },
            {
                {4,5,6,7}
            }
        };
        inline int reps[2] = {2,2};
        inline auto array_a = cast<int>(array);
        inline auto reps_a  = cast<int>(reps);
        inline auto array_v = cast(array,kind::nested_vec);
        inline auto array_d = cast(array,kind::dynamic);
        inline auto array_f = cast(array,kind::fixed);
        inline auto array_h = cast(array,kind::hybrid);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline int dim = 3;
        inline int shape[3] = {2,2,8};
        inline int result[2][2][8] = {
            {
                {0,1,2,3,0,1,2,3},
                {0,1,2,3,0,1,2,3},
            },
            {
                {4,5,6,7,4,5,6,7},
                {4,5,6,7,4,5,6,7},
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        inline int array[2][1][4] = {
            {
                {0,1,2,3},
            },
            {
                {4,5,6,7}
            }
        };
        inline int reps[3] = {2,1,2};
        inline auto array_a = cast<int>(array);
        inline auto reps_a  = cast<int>(reps);
        inline auto array_v = cast(array,kind::nested_vec);
        inline auto array_d = cast(array,kind::dynamic);
        inline auto array_f = cast(array,kind::fixed);
        inline auto array_h = cast(array,kind::hybrid);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        inline int dim = 3;
        inline int shape[3] = {4,1,8};
        inline int result[4][1][8] = {
            {
                {0,1,2,3,0,1,2,3},
            },
            {
                {4,5,6,7,4,5,6,7},
            },
            {
                {0,1,2,3,0,1,2,3},
            },
            {
                {4,5,6,7,4,5,6,7},
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        inline int array[3] = {0,1,2};
        inline int reps[1]  = {2};
        inline auto array_a = cast<int>(array);
        inline auto reps_a  = cast<int>(reps);
        inline auto array_v = cast(array,kind::nested_vec);
        inline auto array_d = cast(array,kind::dynamic);
        inline auto array_f = cast(array,kind::fixed);
        inline auto array_h = cast(array,kind::hybrid);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        inline int dim = 1;
        inline int shape[1] = {6};
        inline int result[6] = {0,1,2,0,1,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        inline int array[3] = {0,1,2};
        inline int reps[2]  = {1,2};
        inline auto array_a = cast<int>(array);
        inline auto reps_a  = cast<int>(reps);
        inline auto array_v = cast(array,kind::nested_vec);
        inline auto array_d = cast(array,kind::dynamic);
        inline auto array_f = cast(array,kind::fixed);
        inline auto array_h = cast(array,kind::hybrid);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        inline int dim = 2;
        inline int shape[2] = {1,6};
        inline int result[1][6] = {{0,1,2,0,1,2}};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        inline int array[3] = {0,1,2};
        inline int reps[6]  = {2,1,1,1,1,1};
        inline auto array_a = cast<int>(array);
        inline auto reps_a  = cast<int>(reps);
        inline auto array_v = cast(array,kind::nested_vec);
        inline auto array_d = cast(array,kind::dynamic);
        inline auto array_f = cast(array,kind::fixed);
        inline auto array_h = cast(array,kind::hybrid);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        inline int dim = 6;
        inline int shape[6] = {2,1,1,1,1,3};
        inline int result[2][1][1][1][1][3] = {
            {{{{{0,1,2}}}}},
            {{{{{0,1,2}}}}},
        };
    }
}

#endif // NMTOOLS_TESTING_DATA_ARRAY_TILE_HPP