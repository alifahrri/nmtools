#ifndef NMTOOLS_TESTING_DATA_ARRAY_BROADCAST_TO_HPP
#define NMTOOLS_TESTING_DATA_ARRAY_BROADCAST_TO_HPP

#include "nmtools/testing/testing.hpp"
#include "nmtools/testing/array_cast.hpp"

namespace nm = nmtools;
namespace na = nm::array;
namespace kind = na::kind;

NMTOOLS_TESTING_DECLARE_CASE(broadcast_to)
{
    using namespace nmtools::literals;

    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline int8_t x[3] = {1,2,3};
        inline auto shape = nmtools_array{1,3};
        inline auto shape_ct = nmtools_tuple{1_ct,3_ct};
        inline auto shape_cl = nmtools_tuple{"1:[1]"_ct, "3:[3]"_ct};
        NMTOOLS_CAST_ARRAYS(x)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline int8_t expected[1][3] = {
            {1,2,3}
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case7)
    {
        inline int8_t x[1][3] = {{1,2,3}};
        inline auto shape = nmtools_array{3,3};
        inline auto shape_ct = nmtools_tuple{3_ct,3_ct};
        inline auto shape_cl = nmtools_tuple{"3:[3]"_ct, "3:[3]"_ct};
        NMTOOLS_CAST_ARRAYS(x)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case7)
    {
        inline int8_t expected[3][3] = {
            {1,2,3},
            {1,2,3},
            {1,2,3}
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case10)
    {
        inline int8_t x = 1;
        inline auto shape = nmtools_array{1,3};
        inline auto shape_ct = nmtools_tuple{1_ct,3_ct};
        inline auto shape_cl = nmtools_tuple{"1:[1]"_ct, "3:[3]"_ct};
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case10)
    {
        inline int8_t expected[1][3] = {
            {1,1,1}
        };
    }

#ifndef NMTOOLS_TESTING_MINIMIZE_FOOTPRINT

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        inline int8_t x[3] = {1,2,3};
        inline auto shape = nmtools_array{3,3};
        inline auto shape_ct = nmtools_tuple{3_ct,3_ct};
        inline auto shape_cl = nmtools_tuple{"3:[3]"_ct,"3:[3]"_ct};
        NMTOOLS_CAST_ARRAYS(x)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        inline int8_t expected[3][3] = {
            {1,2,3},
            {1,2,3},
            {1,2,3}
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        inline int8_t x[3] = {1,2,3};
        inline auto shape = nmtools_array{2,3,3};
        inline auto shape_ct = nmtools_tuple{2_ct,3_ct,3_ct};
        inline auto shape_cl = nmtools_tuple{"2:[2]"_ct,"3:[3]"_ct,"3:[3]"_ct};
        NMTOOLS_CAST_ARRAYS(x)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        inline int8_t expected[2][3][3] = {
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
        inline int8_t x[3][1] = {
            {1},
            {2},
            {3}
        };
        inline auto shape = nmtools_array{3,3};
        inline auto shape_ct = nmtools_tuple{3_ct,3_ct};
        inline auto shape_cl = nmtools_tuple{"3:[3]"_ct,"3:[3]"_ct};
        NMTOOLS_CAST_ARRAYS(x)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        inline int8_t expected[3][3] = {
            {1,1,1},
            {2,2,2},
            {3,3,3}
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        inline int8_t x[3][1] = {
            {1},
            {2},
            {3}
        };
        inline auto shape = nmtools_array{2,3,3};
        inline auto shape_ct = nmtools_tuple{2_ct,3_ct,3_ct};
        inline auto shape_cl = nmtools_tuple{"2:[2]"_ct,"3:[3]"_ct,"3:[3]"_ct};
        NMTOOLS_CAST_ARRAYS(x)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        inline int8_t expected[2][3][3] = {
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
        inline int8_t x[1][3] = {{1,2,3}};
        inline auto shape = nmtools_array{1,3};
        inline auto shape_ct = nmtools_tuple{1_ct,3_ct};
        inline auto shape_cl = nmtools_tuple{"1:[1]"_ct,"3:[3]"_ct};
        NMTOOLS_CAST_ARRAYS(x)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case6)
    {
        inline int8_t expected[1][3] = {
            {1,2,3}
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case8)
    {
        inline int8_t x[1][3] = {{1,2,3}};
        inline auto shape = nmtools_array{2,3,3};
        inline auto shape_ct = nmtools_tuple{2_ct,3_ct,3_ct};
        inline auto shape_cl = nmtools_tuple{"2:[2]"_ct,"3:[3]"_ct,"3:[3]"_ct};
        NMTOOLS_CAST_ARRAYS(x)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case8)
    {
        inline int8_t expected[2][3][3] = {
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
        inline int8_t x[2][1][3] = {
            {
                {1,2,3}
            },
            {
                {4,5,6}
            },
        };
        inline auto shape = nmtools_array{2,3,3};
        inline auto shape_ct = nmtools_tuple{2_ct,3_ct,3_ct};
        inline auto shape_cl = nmtools_tuple{"2:[2]"_ct,"3:[3]"_ct,"3:[3]"_ct};
        NMTOOLS_CAST_ARRAYS(x)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case9)
    {
        inline int8_t expected[2][3][3] = {
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

    NMTOOLS_TESTING_DECLARE_ARGS(case11)
    {
        inline int8_t x = 1;
        inline auto shape = None;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case11)
    {
        inline int8_t expected = 1;
    }
#endif // NMTOOLS_TESTING_MINIMIZE_FOOTPRINT
}

NMTOOLS_TESTING_DECLARE_CASE(broadcast_to_constexpr)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        constexpr int8_t x[3] = {1,2,3};
        constexpr auto shape = nmtools_array{2,3,3};
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        constexpr int8_t expected[2][3][3] = {
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

NMTOOLS_TESTING_DECLARE_CASE(constexpr_broadcast_to)
{
    using namespace nmtools::literals;

    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        constexpr inline int8_t x[3] = {1,2,3};
        constexpr inline auto shape = nmtools_array{1,3};
        constexpr inline auto shape_ct = nmtools_tuple{1_ct,3_ct};
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(x)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        constexpr inline int8_t expected[1][3] = {
            {1,2,3}
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case7)
    {
        constexpr inline int8_t x[1][3] = {{1,2,3}};
        constexpr inline auto shape = nmtools_array{3,3};
        constexpr inline auto shape_ct = nmtools_tuple{3_ct,3_ct};
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(x)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case7)
    {
        constexpr inline int8_t expected[3][3] = {
            {1,2,3},
            {1,2,3},
            {1,2,3}
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case10)
    {
        constexpr inline int8_t x = 1;
        constexpr inline auto shape = nmtools_array{1,3};
        constexpr inline auto shape_ct = nmtools_tuple{1_ct,3_ct};
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case10)
    {
        constexpr inline int8_t expected[1][3] = {
            {1,1,1}
        };
    }
}

#endif // NMTOOLS_TESTING_DATA_ARRAY_BROADCAST_TO_HPP