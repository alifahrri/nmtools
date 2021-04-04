#ifndef NMTOOLS_TESTING_DATA_ARRAY_BROADCAST_TO_HPP
#define NMTOOLS_TESTING_DATA_ARRAY_BROADCAST_TO_HPP

#include "nmtools/array/ndarray/dynamic.hpp"
#include "nmtools/array/ndarray/hybrid.hpp"
#include "nmtools/array/ndarray/fixed.hpp"
#include "nmtools/array/kind.hpp"

#include "nmtools/testing/doctest.hpp"

#include <vector>
#include <array>
#include <tuple>

namespace nm = nmtools;
namespace na = nm::array;
namespace kind = na::kind;

#define CAST_ARRAYS(name) \
inline auto name##_a = cast(name, kind::nested_arr); \
inline auto name##_v = cast(name, kind::nested_vec); \
inline auto name##_f = cast(name, kind::fixed); \
inline auto name##_d = cast(name, kind::dynamic); \
inline auto name##_h = cast(name, kind::hybrid); \

NMTOOLS_TESTING_DECLARE_CASE(broadcast_to)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        int x[3] = {1,2,3};
        auto shape = std::array{1,3};
        CAST_ARRAYS(x)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        int expected[1][3] = {
            {1,2,3}
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        int x[3] = {1,2,3};
        auto shape = std::array{3,3};
        CAST_ARRAYS(x)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        int expected[3][3] = {
            {1,2,3},
            {1,2,3},
            {1,2,3}
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        int x[3] = {1,2,3};
        auto shape = std::array{2,3,3};
        CAST_ARRAYS(x)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        int expected[2][3][3] = {
            {
                {1,2,3},
                {1,2,3},
                {1,2,3},
            },
            {
                {1,2,3},
                {1,2,3},
                {1,2,3},
            },
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        int x[3][1] = {
            {1},
            {2},
            {3}
        };
        auto shape = std::array{3,3};
        CAST_ARRAYS(x)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        int expected[3][3] = {
            {1,1,1},
            {2,2,2},
            {3,3,3}
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        int x[3][1] = {
            {1},
            {2},
            {3}
        };
        auto shape = std::array{2,3,3};
        CAST_ARRAYS(x)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        int expected[2][3][3] = {
            {
                {1,1,1},
                {2,2,2},
                {3,3,3}
            },
            {
                {1,1,1},
                {2,2,2},
                {3,3,3}
            },
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case6)
    {
        int x[1][3] = {{1,2,3}};
        auto shape = std::array{1,3};
        CAST_ARRAYS(x)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case6)
    {
        int expected[1][3] = {
            {1,2,3}
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case7)
    {
        int x[1][3] = {{1,2,3}};
        auto shape = std::array{3,3};
        CAST_ARRAYS(x)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case7)
    {
        int expected[3][3] = {
            {1,2,3},
            {1,2,3},
            {1,2,3}
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case8)
    {
        int x[1][3] = {{1,2,3}};
        auto shape = std::array{2,3,3};
        CAST_ARRAYS(x)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case8)
    {
        int expected[2][3][3] = {
            {
                {1,2,3},
                {1,2,3},
                {1,2,3},
            },
            {
                {1,2,3},
                {1,2,3},
                {1,2,3},
            },
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case9)
    {
        int x[2][1][3] = {
            {
                {1,2,3}
            },
            {
                {4,5,6}
            },
        };
        auto shape = std::array{2,3,3};
        CAST_ARRAYS(x)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case9)
    {
        int expected[2][3][3] = {
            {
                {1,2,3},
                {1,2,3},
                {1,2,3},
            },
            {
                {4,5,6},
                {4,5,6},
                {4,5,6},
            },
        };
    }
}

NMTOOLS_TESTING_DECLARE_CASE(broadcast_to_constexpr)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        constexpr int x[3] = {1,2,3};
        constexpr auto shape = std::array{2,3,3};
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        constexpr int expected[2][3][3] = {
            {
                {1,2,3},
                {1,2,3},
                {1,2,3},
            },
            {
                {1,2,3},
                {1,2,3},
                {1,2,3},
            },
        };
    }
}

#undef CAST_ARRAYS

#endif // NMTOOLS_TESTING_DATA_ARRAY_BROADCAST_TO_HPP