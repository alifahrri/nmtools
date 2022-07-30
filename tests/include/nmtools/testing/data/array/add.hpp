#ifndef NMTOOLS_TESTING_DATA_ARRAY_ADD_HPP
#define NMTOOLS_TESTING_DATA_ARRAY_ADD_HPP

#include "nmtools/testing/testing.hpp"
#include "nmtools/testing/array_cast.hpp"

namespace nm = nmtools;
namespace na = nm::array;
namespace view = nm::view;
namespace kind = na::kind;

NMTOOLS_TESTING_DECLARE_CASE(view, add)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline int8_t a[3][3] = {
            {0,1,2},
            {3,4,5},
            {6,7,8},
        };
        inline int8_t b[3] = {0,1,2};
        NMTOOLS_CAST_ARRAYS(a)
        NMTOOLS_CAST_ARRAYS(b)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline int8_t shape[2] = {3,3};
        inline int8_t result[3][3] = {
            {0, 2, 4},
            {3, 5, 7},
            {6, 8,10},
        };
    }

#ifndef NMTOOLS_TESTING_MINIMIZE_FOOTPRINT
    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        inline int8_t a[3][3] = {
            {0,1,2},
            {3,4,5},
            {6,7,8},
        };
        inline int8_t b = 1;
        NMTOOLS_CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        inline int8_t shape[2] = {3,3};
        inline int8_t result[3][3] = {
            {1,2,3},
            {4,5,6},
            {7,8,9},
        };
    }
#endif // NMTOOLS_TESTING_MINIMIZE_FOOTPRINT

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        inline int8_t a = 1;
        inline int8_t b = 1;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        inline auto shape = None;
        inline int8_t result = 2;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        inline int8_t a[3][2] = {
            {0,1},
            {2,3},
            {4,5},
        };
        inline int8_t b = 1;
        NMTOOLS_CAST_ARRAYS(a);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        inline int8_t shape[2] = {3,2};
        inline int8_t result[3][2] = {
            {1,2},
            {3,4},
            {5,6},
        };
    }
}

// TODO: rename to NMTOOLS_TESTING_DECLARE_CASE(array, constexpr_add)
NMTOOLS_TESTING_DECLARE_CASE(view, constexpr_add)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        constexpr int8_t a[3][3] = {
            {0,1,2},
            {3,4,5},
            {6,7,8},
        };
        constexpr int8_t b[3] = {0,1,2};
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(a)
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(b)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        constexpr int8_t shape[2] = {3,3};
        constexpr int8_t result[3][3] = {
            {0, 2, 4},
            {3, 5, 7},
            {6, 8,10},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        constexpr inline int8_t a[3][3] = {
            {0,1,2},
            {3,4,5},
            {6,7,8},
        };
        constexpr inline int8_t b = 1;
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        constexpr inline int8_t shape[2] = {3,3};
        constexpr inline int8_t result[3][3] = {
            {1,2,3},
            {4,5,6},
            {7,8,9},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        constexpr inline int8_t a = 1;
        constexpr inline int8_t b = 1;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        constexpr inline auto shape = None;
        constexpr inline int8_t result = 2;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        constexpr inline int8_t a[3][2] = {
            {0,1},
            {2,3},
            {4,5},
        };
        constexpr inline int8_t b = 1;
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(a);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        constexpr inline int8_t shape[2] = {3,2};
        constexpr inline int8_t result[3][2] = {
            {1,2},
            {3,4},
            {5,6},
        };
    }
}

NMTOOLS_TESTING_DECLARE_CASE(array, constexpr_reduce_add)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        constexpr inline int8_t a[2][3][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
            },
            {
                { 6,  7},
                { 8,  9},
                {10, 11},
            }
        };
        constexpr inline int8_t axis = 0;
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        constexpr inline int8_t shape[2] = {3,2};
        constexpr inline int8_t result[3][2] = {
            { 6, 8},
            {10,12},
            {14,16},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        // use a from case1 to save space
        using case1::args::a;
        constexpr inline int8_t axis[2] = {0,1};
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(a)
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(axis)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        constexpr inline int8_t shape[1]  = {2};
        constexpr inline int8_t result[2] = {30,36};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case9)
    {
        // use a from case1 to save space
        using case1::args::a;
        constexpr inline int8_t axis = 0;
        constexpr inline auto dtype = None;
        constexpr inline auto initial = None;
        constexpr inline auto keepdims = True;
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case9)
    {
        constexpr inline int8_t shape[3] = {1,3,2};
        constexpr inline int8_t result[1][3][2] = {
            {
                { 6, 8},
                {10,12},
                {14,16},
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case14)
    {
        // use a from case1 to save space
        using case1::args::a;
        constexpr inline int8_t axis[2] = {1,2};
        constexpr inline auto dtype = None;
        constexpr inline auto initial = None;
        constexpr inline auto keepdims = false;
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(a)
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(axis)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case14)
    {
        constexpr inline int8_t shape[1]  = {2};
        constexpr inline int8_t result[2] = {15,51};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case15)
    {
        // use a from case1 to save space
        using case1::args::a;
        constexpr inline auto axis = None;
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case15)
    {
        constexpr inline auto shape = None;
        constexpr inline int8_t result = 66;
    }
}

NMTOOLS_TESTING_DECLARE_CASE(view, reduce_add)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline int8_t a[2][3][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
            },
            {
                { 6,  7},
                { 8,  9},
                {10, 11},
            }
        };
        inline int8_t axis = 0;
        NMTOOLS_CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline int8_t shape[2] = {3,2};
        inline int8_t result[3][2] = {
            { 6, 8},
            {10,12},
            {14,16},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        // use a from case1 to save space
        using case1::args::a;
        inline int8_t axis[2] = {0,1};
        NMTOOLS_CAST_ARRAYS(a)
        NMTOOLS_CAST_INDEX_ARRAYS(axis)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        inline int8_t shape[1]  = {2};
        inline int8_t result[2] = {30,36};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case9)
    {
        // use a from case1 to save space
        using case1::args::a;
        inline int8_t axis = 0;
        inline auto dtype = None;
        inline auto initial = None;
        inline auto keepdims = True;
        NMTOOLS_CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case9)
    {
        inline int8_t shape[3] = {1,3,2};
        inline int8_t result[1][3][2] = {
            {
                { 6, 8},
                {10,12},
                {14,16},
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case14)
    {
        // use a from case1 to save space
        using case1::args::a;
        inline int8_t axis[2] = {1,2};
        inline auto dtype = None;
        inline auto initial = None;
        inline auto keepdims = false;
        NMTOOLS_CAST_ARRAYS(a)
        NMTOOLS_CAST_INDEX_ARRAYS(axis)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case14)
    {
        inline int8_t shape[1]  = {2};
        inline int8_t result[2] = {15,51};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case15)
    {
        // use a from case1 to save space
        using case1::args::a;
        inline auto axis = None;
        NMTOOLS_CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case15)
    {
        inline auto shape = None;
        inline int8_t result = 66;
    }

#ifndef NMTOOLS_TESTING_MINIMIZE_FOOTPRINT
    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        inline int8_t a[2][3][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
            },
            {
                { 6,  7},
                { 8,  9},
                {10, 11},
            }
        };
        inline int8_t axis = 1;
        NMTOOLS_CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        inline int8_t shape[2] = {2,2};
        inline int8_t result[2][2] = {
            { 6, 9},
            {24,27},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        inline int8_t a[2][3][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
            },
            {
                { 6,  7},
                { 8,  9},
                {10, 11},
            }
        };
        inline int8_t axis = 2;
        NMTOOLS_CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        inline int8_t shape[2] = {2,3};
        inline int8_t result[2][3] = {
            { 1,  5,  9},
            {13, 17, 21}
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        inline int8_t a[2][3][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
            },
            {
                { 6,  7},
                { 8,  9},
                {10, 11},
            }
        };
        inline int8_t axis[2] = {0,2};
        NMTOOLS_CAST_ARRAYS(a)
        NMTOOLS_CAST_INDEX_ARRAYS(axis)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        inline int8_t shape[1]  = {3};
        inline int8_t result[3] = {14,22,30};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case6)
    {
        inline int8_t a[2][3][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
            },
            {
                { 6,  7},
                { 8,  9},
                {10, 11},
            }
        };
        inline int8_t axis[2] = {1,2};
        NMTOOLS_CAST_ARRAYS(a)
        NMTOOLS_CAST_INDEX_ARRAYS(axis)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case6)
    {
        inline int8_t shape[1]  = {2};
        inline int8_t result[2] = {15,51};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case7)
    {
        inline uint8_t a[2][3][2] = {
            {
                {255, 1},
                {  2, 3},
                {  4, 5},
            },
            {
                { 6,  7},
                { 8,  9},
                {10, 11},
            }
        };
        inline int8_t axis = 0;
        // must provide dtype for correct result
        inline auto dtype = int16;
        NMTOOLS_CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case7)
    {
        inline int8_t shape[2] = {3,2};
        inline int16_t result[3][2] = {
            {261, 8},
            { 10,12},
            { 14,16},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case8)
    {
        inline uint8_t a[2][3][2] = {
            {
                {  0, 1},
                {  2, 3},
                {  4, 5},
            },
            {
                { 6,  7},
                { 8,  9},
                {10, 11},
            }
        };
        inline int8_t axis = 2;
        // must provide dtype for correct result
        inline auto dtype = int16;
        inline auto initial = 255;
        NMTOOLS_CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case8)
    {
        inline int8_t shape[2] = {2,3};
        inline int16_t result[2][3] = {
            {256,260,264},
            {268,272,276},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case10)
    {
        inline int8_t a[2][3][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
            },
            {
                { 6,  7},
                { 8,  9},
                {10, 11},
            }
        };
        inline int8_t axis = 1;
        inline auto dtype = None;
        inline auto initial = None;
        inline auto keepdims = False;
        NMTOOLS_CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case10)
    {
        inline int8_t shape[2] = {2,2};
        inline int8_t result[2][2] = {
            { 6, 9},
            {24,27},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case11)
    {
        inline int8_t a[2][3][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
            },
            {
                { 6,  7},
                { 8,  9},
                {10, 11},
            }
        };
        inline auto dtype = None;
        inline auto initial = None;
        inline auto keepdims = true;
        inline int8_t axis = 2;
        NMTOOLS_CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case11)
    {
        inline int8_t shape[3] = {2,3,1};
        inline int8_t result[2][3][1] = {
            {
                {1},
                {5},
                {9}
            },
            {
                {13},
                {17},
                {21}
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case12)
    {
        inline int8_t a[2][3][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
            },
            {
                { 6,  7},
                { 8,  9},
                {10, 11},
            }
        };
        inline int8_t axis[2] = {0,1};
        inline auto dtype = None;
        inline auto initial = None;
        inline auto keepdims = false;
        NMTOOLS_CAST_ARRAYS(a)
        NMTOOLS_CAST_INDEX_ARRAYS(axis)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case12)
    {
        inline int8_t shape[1]  = {2};
        inline int8_t result[2] = {30,36};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case13)
    {
        inline int8_t a[2][3][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
            },
            {
                { 6,  7},
                { 8,  9},
                {10, 11},
            }
        };
        inline int8_t axis[2] = {0,2};
        inline auto dtype = None;
        inline auto initial = None;
        inline auto keepdims = true;
        NMTOOLS_CAST_ARRAYS(a)
        NMTOOLS_CAST_INDEX_ARRAYS(axis)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case13)
    {
        inline int8_t shape[3]  = {1,3,1};
        inline int8_t result[1][3][1] = {
            {
                {14},
                {22},
                {30},
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case16)
    {
        inline int8_t a[2][3][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
            },
            {
                { 6,  7},
                { 8,  9},
                {10, 11},
            }
        };
        inline auto axis = None;
        inline auto initial = 10;
        NMTOOLS_CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case16)
    {
        inline auto shape = None;
        inline int8_t result = 76;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case17)
    {
        inline int8_t a[2][3][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
            },
            {
                { 6,  7},
                { 8,  9},
                {10, 11},
            }
        };
        inline auto axis = None;
        inline auto initial = 10;
        inline auto keepdims = False;
        NMTOOLS_CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case17)
    {
        inline auto shape = None;
        inline int8_t result = 76;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case18)
    {
        inline int8_t a[2][3][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
            },
            {
                { 6,  7},
                { 8,  9},
                {10, 11},
            }
        };
        inline auto axis = None;
        inline auto initial = 10;
        inline auto keepdims = True;
        NMTOOLS_CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case18)
    {
        inline int8_t shape[3] = {1,1,1};
        inline int8_t result[1][1][1] = {{{76}}};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case19)
    {
        inline int8_t a[2][3][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
            },
            {
                { 6,  7},
                { 8,  9},
                {10, 11},
            }
        };
        inline auto axis = None;
        inline auto initial = 10;
        inline auto keepdims = true;
        NMTOOLS_CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case19)
    {
        using shape_t = meta::make_either_type_t<none_t,nmtools_array<uint8_t,3>>;
        inline auto shape = shape_t(nmtools_array{(uint8_t)1,(uint8_t)1,(uint8_t)1});
        inline int8_t result[1][1][1] = {{{76}}};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case20)
    {
        inline int8_t a[2][3][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
            },
            {
                { 6,  7},
                { 8,  9},
                {10, 11},
            }
        };
        inline auto axis = None;
        inline auto initial = 10;
        inline auto keepdims = false;
        NMTOOLS_CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case20)
    {
        // using shape_t = std::variant<none_t,std::array<size_t,1>>;
        // inline auto shape = shape_t{None};
        inline auto shape = None;
        inline int8_t result = 76;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case21)
    {
        inline int8_t a[2][3][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
            },
            {
                { 6,  7},
                { 8,  9},
                {10, 11},
            }
        };
        inline int8_t axis = 0;
        inline auto dtype = float32;
        NMTOOLS_CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case21)
    {
        inline int8_t shape[2] = {3,2};
        inline float result[3][2] = {
            { 6.f, 8.f},
            {10.f,12.f},
            {14.f,16.f},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case22)
    {
        using namespace literals;
        inline int8_t a[2][3][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
            },
            {
                { 6,  7},
                { 8,  9},
                {10, 11},
            }
        };
        inline auto axis = 0_ct;
        inline auto dtype = float32;
        NMTOOLS_CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case22)
    {
        inline int8_t shape[2] = {3,2};
        inline float result[3][2] = {
            { 6.f, 8.f},
            {10.f,12.f},
            {14.f,16.f},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case23)
    {
        inline int8_t a[2][3][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
            },
            {
                { 6,  7},
                { 8,  9},
                {10, 11},
            }
        };
        NMTOOLS_CAST_ARRAYS(a)
        inline auto axis = None;
        inline auto keepdims = True;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case23)
    {
        inline int8_t shape[3] = {1,1,1};
        inline int8_t result[1][1][1] = {{{66}}};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case24)
    {
        inline int8_t a[2][3][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
            },
            {
                { 6,  7},
                { 8,  9},
                {10, 11},
            }
        };
        NMTOOLS_CAST_ARRAYS(a)
        inline auto axis = None;
        inline auto keepdims = False;
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case24)
    {
        inline auto shape = None;
        inline int8_t result = 66;
    }
#endif // NMTOOLS_TESTING_MINIMIZE_FOOTPRINT
}

NMTOOLS_TESTING_DECLARE_CASE(view, accumulate_add)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline int8_t a[2][3][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
            },
            {
                { 6,  7},
                { 8,  9},
                {10, 11},
            }
        };
        inline int8_t axis = 0;
        NMTOOLS_CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline int8_t shape[3] = {2,3,2};
        inline int8_t result[2][3][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
            },
            {
                { 6,  8},
                {10, 12},
                {14, 16},
            } 
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        // use a from case1 to save space
        using case1::args::a;
        inline int8_t axis = 1;
        NMTOOLS_CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        inline int8_t shape[3] = {2,3,2};
        inline int8_t result[2][3][2] = {
            {
                {0,1},
                {2,4},
                {6,9},
            },
            {
                { 6,  7},
                {14, 16},
                {24, 27},
            } 
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        // use a from case1 to save space
        using case1::args::a;
        inline int8_t axis = 2;
        NMTOOLS_CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        inline int8_t shape[3] = {2,3,2};
        inline int8_t result[2][3][2] = {
            {
                {0,1},
                {2,5},
                {4,9},
            },
            {
                { 6, 13},
                { 8, 17},
                {10, 21},
            } 
        };
    }
}

NMTOOLS_TESTING_DECLARE_CASE(array, constexpr_accumulate_add)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        constexpr inline int8_t a[2][3][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
            },
            {
                { 6,  7},
                { 8,  9},
                {10, 11},
            }
        };
        constexpr inline int8_t axis = 0;
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        constexpr inline int8_t shape[3] = {2,3,2};
        constexpr inline int8_t result[2][3][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
            },
            {
                { 6,  8},
                {10, 12},
                {14, 16},
            } 
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        // use a from case1 to save space
        using case1::args::a;
        constexpr inline int8_t axis = 1;
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        constexpr inline int8_t shape[3] = {2,3,2};
        constexpr inline int8_t result[2][3][2] = {
            {
                {0,1},
                {2,4},
                {6,9},
            },
            {
                { 6,  7},
                {14, 16},
                {24, 27},
            } 
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        // use a from case1 to save space
        using case1::args::a;
        constexpr inline int8_t axis = 2;
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        constexpr inline int8_t shape[3] = {2,3,2};
        constexpr inline int8_t result[2][3][2] = {
            {
                {0,1},
                {2,5},
                {4,9},
            },
            {
                { 6, 13},
                { 8, 17},
                {10, 21},
            } 
        };
    }
}

NMTOOLS_TESTING_DECLARE_CASE(view, outer_add)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline int8_t a[2][3] = {
            {0,1,2},
            {3,4,5},
        };
        inline int8_t b[3] = { 6,  7, 8};
        NMTOOLS_CAST_ARRAYS(a)
        NMTOOLS_CAST_ARRAYS(b)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline int8_t shape[3] = {2,3,3};
        inline int8_t result[2][3][3] = \
           {{{ 6,  7,  8},
            { 7,  8,  9},
            { 8,  9, 10}},

           {{ 9, 10, 11},
            {10, 11, 12},
            {11, 12, 13}}};
    }
}

NMTOOLS_TESTING_DECLARE_CASE(array, constexpr_outer_add)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        constexpr inline int8_t a[2][3] = {
            {0,1,2},
            {3,4,5},
        };
        constexpr inline int8_t b[3] = { 6,  7, 8};
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(a)
        NMTOOLS_CONSTEXPR_CAST_ARRAYS(b)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        constexpr inline int8_t shape[3] = {2,3,3};
        constexpr inline int8_t result[2][3][3] = \
           {{{ 6,  7,  8},
            { 7,  8,  9},
            { 8,  9, 10}},

           {{ 9, 10, 11},
            {10, 11, 12},
            {11, 12, 13}}};
    }
}

#endif // NMTOOLS_TESTING_DATA_ARRAY_ADD_HPP