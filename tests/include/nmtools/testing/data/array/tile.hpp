#ifndef NMTOOLS_TESTING_DATA_ARRAY_TILE_HPP
#define NMTOOLS_TESTING_DATA_ARRAY_TILE_HPP

#include "nmtools/testing/testing.hpp"
#include "nmtools/testing/array_cast.hpp"

namespace nm = nmtools;
namespace na = nm::array;
namespace kind = na::kind;

NMTOOLS_TESTING_DECLARE_CASE(view, tile)
{
    using namespace nmtools::literals;

    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline int8_t array[2][1][4] = {
            {
                {0,1,2,3},
            },
            {
                {4,5,6,7}
            }
        };
        inline int8_t reps[2] = {2,2};
        inline auto reps_ct = nmtools_tuple{2_ct,2_ct};
        NMTOOLS_CAST_ARRAYS(array)
        NMTOOLS_CAST_ARRAYS(reps)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline int8_t dim = 3;
        inline int8_t shape[3] = {2,2,8};
        inline int8_t result[2][2][8] = {
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

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        inline int8_t array[3] = {0,1,2};
        inline int8_t reps[1]  = {2};
        NMTOOLS_CAST_ARRAYS(array)
        NMTOOLS_CAST_ARRAYS(reps)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        inline int8_t dim = 1;
        inline int8_t shape[1] = {6};
        inline int8_t result[6] = {0,1,2,0,1,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        inline int8_t array[3] = {0,1,2};
        inline int8_t reps[6]  = {2,1,1,1,1,1};
        NMTOOLS_CAST_ARRAYS(array)
        NMTOOLS_CAST_ARRAYS(reps)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        inline int8_t dim = 6;
        inline int8_t shape[6] = {2,1,1,1,1,3};
        inline int8_t result[2][1][1][1][1][3] = {
            {{{{{0,1,2}}}}},
            {{{{{0,1,2}}}}},
        };
    }

#ifndef NMTOOLS_TESTING_MINIMIZE_FOOTPRINT
    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        inline int8_t array[2][1][4] = {
            {
                {0,1,2,3},
            },
            {
                {4,5,6,7}
            }
        };
        inline int8_t reps[3] = {2,1,2};
        NMTOOLS_CAST_ARRAYS(array)
        NMTOOLS_CAST_ARRAYS(reps)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        inline int8_t dim = 3;
        inline int8_t shape[3] = {4,1,8};
        inline int8_t result[4][1][8] = {
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

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        inline int8_t array[3] = {0,1,2};
        inline int8_t reps[2]  = {1,2};
        NMTOOLS_CAST_ARRAYS(array)
        NMTOOLS_CAST_ARRAYS(reps)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        inline int8_t dim = 2;
        inline int8_t shape[2] = {1,6};
        inline int8_t result[1][6] = {{0,1,2,0,1,2}};
    }
#endif // NMTOOLS_TESTING_MINIMIZE_FOOTPRINT
}

NMTOOLS_TESTING_DECLARE_CASE(array, constexpr_tile)
{
    using namespace nmtools::literals;

    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        constexpr inline int8_t array[2][1][4] = {
            {
                {0,1,2,3},
            },
            {
                {4,5,6,7}
            }
        };
        constexpr inline int8_t reps[2] = {2,2};
        constexpr inline auto reps_ct = nmtools_tuple{2_ct,2_ct};
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(array)
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(reps)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        constexpr inline int8_t dim = 3;
        constexpr inline int8_t shape[3] = {2,2,8};
        constexpr inline int8_t result[2][2][8] = {
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

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        constexpr inline int8_t array[3] = {0,1,2};
        constexpr inline int8_t reps[1]  = {2};
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(array)
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(reps)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        constexpr inline int8_t dim = 1;
        constexpr inline int8_t shape[1] = {6};
        constexpr inline int8_t result[6] = {0,1,2,0,1,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        constexpr inline int8_t array[3] = {0,1,2};
        constexpr inline int8_t reps[6]  = {2,1,1,1,1,1};
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(array)
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(reps)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        constexpr inline int8_t dim = 6;
        constexpr inline int8_t shape[6] = {2,1,1,1,1,3};
        constexpr inline int8_t result[2][1][1][1][1][3] = {
            {{{{{0,1,2}}}}},
            {{{{{0,1,2}}}}},
        };
    }
}

#endif // NMTOOLS_TESTING_DATA_ARRAY_TILE_HPP