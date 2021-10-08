#ifndef NMTOOLS_TESTING_DATA_ARRAY_FLIP_HPP
#define NMTOOLS_TESTING_DATA_ARRAY_FLIP_HPP

#include "nmtools/array/ndarray/dynamic.hpp"
#include "nmtools/array/ndarray/hybrid.hpp"
#include "nmtools/array/ndarray/fixed.hpp"
#include "nmtools/array/kind.hpp"

#include "nmtools/testing/testing.hpp"

#include <vector>
#include <array>
#include <tuple>

namespace nm = nmtools;
namespace na = nm::array;
namespace kind = na::kind;

#ifndef PLATFORMIO
#define CAST_ARRAYS(name) \
inline auto name##_a = cast(name, kind::nested_arr); \
inline auto name##_v = cast(name, kind::nested_vec); \
inline auto name##_f = cast(name, kind::fixed); \
inline auto name##_d = cast(name, kind::dynamic); \
inline auto name##_h = cast(name, kind::hybrid);
#else
#define CAST_ARRAYS(name) \
inline auto name##_a = cast(name, kind::nested_arr); \
inline auto name##_f = cast(name, kind::fixed); \
inline auto name##_h = cast(name, kind::hybrid);
#endif // PLATFORMIO

NMTOOLS_TESTING_DECLARE_CASE(flip)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline int array[2][2][2] = {
            {
                {0,1},
                {2,3},
            },
            {
                {4,5},
                {6,7},
            }
        };
        inline auto axis = None;
        CAST_ARRAYS(array)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline int result[2][2][2] = {
            {
                {7,6},
                {5,4},
            },
            {
                {3,2},
                {1,0},
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        inline int array[2][2][2] = {
            {
                {0,1},
                {2,3},
            },
            {
                {4,5},
                {6,7},
            }
        };
        inline auto axis = 0;
        CAST_ARRAYS(array)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        inline int result[2][2][2] = {
            {
                {4,5},
                {6,7},
            },
            {
                {0,1},
                {2,3},
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        inline int array[2][2][2] = {
            {
                {0,1},
                {2,3},
            },
            {
                {4,5},
                {6,7},
            }
        };
        inline auto axis = 1;
        CAST_ARRAYS(array)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        inline int result[2][2][2] = {
            {
                {2,3},
                {0,1},
            },
            {
                {6,7},
                {4,5},
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        inline int array[2][2][2] = {
            {
                {0,1},
                {2,3},
            },
            {
                {4,5},
                {6,7},
            }
        };
        inline int axis[2] = {0,2};
        CAST_ARRAYS(array)
        CAST_ARRAYS(axis)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        inline int result[2][2][2] = {
            {
                {5,4},
                {7,6},
            },
            {
                {1,0},
                {3,2},
            }
        };
    }
}

NMTOOLS_TESTING_DECLARE_CASE(constexpr_flip)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        constexpr int array[2][2][2] = {
            {
                {0,1},
                {2,3},
            },
            {
                {4,5},
                {6,7},
            }
        };
        constexpr auto axis = None;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        constexpr int result[2][2][2] = {
            {
                {7,6},
                {5,4},
            },
            {
                {3,2},
                {1,0},
            }
        };
    }
}

#undef CAST_ARRAYS

#endif // NMTOOLS_TESTING_DATA_ARRAY_FLIP_HPP