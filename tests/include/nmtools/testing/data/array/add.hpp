#ifndef NMTOOLS_TESTING_DATA_ARRAY_ADD_HPP
#define NMTOOLS_TESTING_DATA_ARRAY_ADD_HPP

#include "nmtools/array/ndarray/dynamic.hpp"
#include "nmtools/array/ndarray/hybrid.hpp"
#include "nmtools/array/ndarray/fixed.hpp"
#include "nmtools/testing/doctest.hpp"

#include <vector>
#include <array>

namespace nm = nmtools;
namespace na = nm::array;
namespace view = nm::view;
namespace kind = na::kind;

#define CAST_ARRAYS(name) \
inline auto name##_a = cast(name, kind::nested_arr); \
inline auto name##_v = cast(name, kind::nested_vec); \
inline auto name##_f = cast(name, kind::fixed); \
inline auto name##_d = cast(name, kind::dynamic); \
inline auto name##_h = cast(name, kind::hybrid); \

NMTOOLS_TESTING_DECLARE_CASE(view, add)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline int a[3][3] = {
            {0,1,2},
            {3,4,5},
            {6,7,8},
        };
        inline int b[3] = {0,1,2};
        CAST_ARRAYS(a)
        CAST_ARRAYS(b)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline int shape[2] = {3,3};
        inline int result[3][3] = {
            {0, 2, 4},
            {3, 5, 7},
            {6, 8,10},
        };
    }
}

NMTOOLS_TESTING_DECLARE_CASE(view, constexpr_add)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        constexpr int a[3][3] = {
            {0,1,2},
            {3,4,5},
            {6,7,8},
        };
        constexpr int b[3] = {0,1,2};
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        constexpr int shape[2] = {3,3};
        constexpr int result[3][3] = {
            {0, 2, 4},
            {3, 5, 7},
            {6, 8,10},
        };
    }
}

NMTOOLS_TESTING_DECLARE_CASE(view, reduce_add)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline int a[2][3][2] = {
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
        inline int axis = 0;
        CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline int shape[2] = {3,2};
        inline int result[3][2] = {
            { 6, 8},
            {10,12},
            {14,16},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        inline int a[2][3][2] = {
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
        inline int axis = 1;
        CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        inline int shape[2] = {2,2};
        inline int result[2][2] = {
            { 6, 9},
            {24,27},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        inline int a[2][3][2] = {
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
        inline int axis = 2;
        CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        inline int shape[2] = {2,3};
        inline int result[2][3] = {
            { 1,  5,  9},
            {13, 17, 21}
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        inline int a[2][3][2] = {
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
        inline int axis[2] = {0,1};
        CAST_ARRAYS(a)
        CAST_ARRAYS(axis)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        inline int shape[1]  = {2};
        inline int result[2] = {30,36};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        inline int a[2][3][2] = {
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
        inline int axis[2] = {0,2};
        CAST_ARRAYS(a)
        CAST_ARRAYS(axis)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        inline int shape[1]  = {3};
        inline int result[3] = {14,22,30};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case6)
    {
        inline int a[2][3][2] = {
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
        inline int axis[2] = {1,2};
        CAST_ARRAYS(a)
        CAST_ARRAYS(axis)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case6)
    {
        inline int shape[1]  = {2};
        inline int result[2] = {15,51};
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
        inline int axis = 0;
        // must provide dtype for correct result
        inline auto dtype = int16;
        CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case7)
    {
        inline int shape[2] = {3,2};
        inline int result[3][2] = {
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
        inline int axis = 2;
        // must provide dtype for correct result
        inline auto dtype = int16;
        inline auto initial = 255;
        CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case8)
    {
        inline int shape[2] = {2,3};
        inline int result[2][3] = {
            {256,260,264},
            {268,272,276},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case9)
    {
        inline int a[2][3][2] = {
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
        inline int axis = 0;
        inline auto dtype = None;
        inline auto initial = None;
        inline auto keepdims = True;
        CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case9)
    {
        inline int shape[3] = {1,3,2};
        inline int result[1][3][2] = {
            {
                { 6, 8},
                {10,12},
                {14,16},
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case10)
    {
        inline int a[2][3][2] = {
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
        inline int axis = 1;
        inline auto dtype = None;
        inline auto initial = None;
        inline auto keepdims = False;
        CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case10)
    {
        inline int shape[2] = {2,2};
        inline int result[2][2] = {
            { 6, 9},
            {24,27},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case11)
    {
        inline int a[2][3][2] = {
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
        inline int axis = 2;
        CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case11)
    {
        inline int shape[3] = {2,3,1};
        inline int result[2][3][1] = {
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
        inline int a[2][3][2] = {
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
        inline int axis[2] = {0,1};
        inline auto dtype = None;
        inline auto initial = None;
        inline auto keepdims = false;
        CAST_ARRAYS(a)
        CAST_ARRAYS(axis)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case12)
    {
        inline int shape[1]  = {2};
        inline int result[2] = {30,36};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case13)
    {
        inline int a[2][3][2] = {
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
        inline int axis[2] = {0,2};
        inline auto dtype = None;
        inline auto initial = None;
        inline auto keepdims = true;
        CAST_ARRAYS(a)
        CAST_ARRAYS(axis)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case13)
    {
        inline int shape[3]  = {1,3,1};
        inline int result[1][3][1] = {
            {
                {14},
                {22},
                {30},
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case14)
    {
        inline int a[2][3][2] = {
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
        inline int axis[2] = {1,2};
        inline auto dtype = None;
        inline auto initial = None;
        inline auto keepdims = false;
        CAST_ARRAYS(a)
        CAST_ARRAYS(axis)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case14)
    {
        inline int shape[1]  = {2};
        inline int result[2] = {15,51};
    }
}

NMTOOLS_TESTING_DECLARE_CASE(view, accumulate_add)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline int a[2][3][2] = {
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
        inline int axis = 0;
        CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline int shape[3] = {2,3,2};
        inline int result[2][3][2] = {
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
        inline int a[2][3][2] = {
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
        inline int axis = 1;
        CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        inline int shape[3] = {2,3,2};
        inline int result[2][3][2] = {
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
        inline int a[2][3][2] = {
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
        inline int axis = 2;
        CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        inline int shape[3] = {2,3,2};
        inline int result[2][3][2] = {
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
        inline int a[2][3] = {
            {0,1,2},
            {3,4,5},
        };
        inline int b[3] = { 6,  7, 8};
        CAST_ARRAYS(a)
        CAST_ARRAYS(b)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline int shape[3] = {2,3,3};
        inline int result[2][3][3] = \
           {{{ 6,  7,  8},
            { 7,  8,  9},
            { 8,  9, 10}},

           {{ 9, 10, 11},
            {10, 11, 12},
            {11, 12, 13}}};
    }
}

#undef CAST_ARRAYS

#endif // NMTOOLS_TESTING_DATA_ARRAY_ADD_HPP