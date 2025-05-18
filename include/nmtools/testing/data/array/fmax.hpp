#ifndef NMTOOLS_TESTING_DATA_ARRAY_FMAX_HPP
#define NMTOOLS_TESTING_DATA_ARRAY_FMAX_HPP

#include "nmtools/testing/testing.hpp"
#include "nmtools/testing/array_cast.hpp"
#include "nmtools/constants.hpp" // Include for None, True, False
#include "nmtools/meta.hpp"      // Required for numeric_limits

namespace nm = nmtools;
namespace na = nm::array;
namespace kind = na::kind;

namespace meta = nm::meta; // Alias for convenience

// Define a constant using nmtools::meta for the initial value for fmax
constexpr float fmax_initial = meta::numeric_limits<float>::min();

NMTOOLS_TESTING_DECLARE_CASE(view, fmax)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline float a[3][3] = {
            {0,1,2},
            {3,4,5},
            {6,7,8},
        };
        inline float b[3] = {0.F,1,NAN};
        NMTOOLS_CAST_ARRAYS(a)
        NMTOOLS_CAST_ARRAYS(b)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline int shape[2] = {3,3};
        inline float result[3][3] = {
            {std::fmax(0.f,0.F),std::fmax(1.f,1.f),std::fmax(2.f,NAN)},
            {std::fmax(3.f,0.F),std::fmax(4.f,1.f),std::fmax(5.f,NAN)},
            {std::fmax(6.f,0.F),std::fmax(7.f,1.f),std::fmax(8.f,NAN)},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        inline float a[3][3] = {
            {0,1,2},
            {3,4,5},
            {6,7,8},
        };
        inline float b = 1.f;
        NMTOOLS_CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        inline int shape[2] = {3,3};
        inline float result[3][3] = {
            {std::fmax(0.f,1.f),std::fmax(1.f,1.f),std::fmax(2.f,1.f)},
            {std::fmax(3.f,1.f),std::fmax(4.f,1.f),std::fmax(5.f,1.f)},
            {std::fmax(6.f,1.f),std::fmax(7.f,1.f),std::fmax(8.f,1.f)},
        };
    }
}

NMTOOLS_TESTING_DECLARE_CASE(view, reduce_fmax)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline float a[2][3][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
            },
            {
                { 6, 7},
                { 8, 9},
                {10,11},
            },
        };
        inline int axis = 0;
        NMTOOLS_CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline int shape[2] = {3,2};
        inline float result[3][2] = {
            { 6, 7},
            { 8, 9},
            {10,11},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        inline float a[2][3][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
            },
            {
                { 6, 7},
                { 8, 9},
                {10,11},
            },
        };
        inline int axis = 1;
        NMTOOLS_CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        inline int shape[2] = {2,2};
        inline float result[2][2] = {
            { 4, 5},
            {10,11},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        inline float a[2][3][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
            },
            {
                { 6, 7},
                { 8, 9},
                {10,11},
            },
        };
        inline int axis = 2;
        NMTOOLS_CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        inline int shape[2] = {2,3};
        inline float result[2][3] = {
            {1, 3,  5},
            {7, 9, 11},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        inline float a[2][3][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
            },
            {
                { 6, 7},
                { 8, 9},
                {10,11},
            },
        };
        inline int axis[2] = {0,1};
        NMTOOLS_CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        inline int shape[1] = {2};
        inline float result[2] = {10,11};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        inline float a[2][3][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
            },
            {
                { 6, 7},
                { 8, 9},
                {10,11},
            },
        };
        inline int axis[2] = {0,2};
        NMTOOLS_CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        inline int shape[1] = {3};
        inline float result[3] = {7,9,11};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case6)
    {
        inline float a[2][3][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
            },
            {
                { 6, 7},
                { 8, 9},
                {10,11},
            },
        };
        inline int axis[2] = {1,2};
        NMTOOLS_CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case6)
    {
        inline int shape[1] = {2};
        inline float result[2] = {5,11};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case7)
    {
        inline uint8_t a[2][3][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
            },
            {
                { 6, 7},
                { 8, 9},
                {10,11},
            },
        };
        inline int axis[2] = {1,2};
        inline auto dtype = float32;
        inline auto initial = 512;
        NMTOOLS_CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case7)
    {
        inline int shape[1] = {2};
        inline float result[2] = {512,512};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case8)
    {
        inline float a[2][3][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
            },
            {
                { 6, 7},
                { 8, 9},
                {10,11},
            },
        };
        inline int axis = 0;
        inline auto dtype = None;
        inline auto initial = None;
        inline auto keepdims = True;
        NMTOOLS_CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case8)
    {
        inline int shape[3] = {1,3,2};
        inline float result[1][3][2] = {
            {
                { 6, 7},
                { 8, 9},
                {10,11},
            }
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case9)
    {
        inline float a[2][3][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
            },
            {
                { 6, 7},
                { 8, 9},
                {10,11},
            },
        };
        inline int axis = 1;
        inline auto dtype = None;
        inline auto initial = None;
        inline auto keepdims = False;
        NMTOOLS_CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case9)
    {
        inline int shape[2] = {2,2};
        inline float result[2][2] = {
            { 4, 5},
            {10,11},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case10)
    {
        inline float a[2][3][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
            },
            {
                { 6, 7},
                { 8, 9},
                {10,11},
            },
        };
        inline int axis = 2;
        inline auto dtype = None;
        inline auto initial = None;
        inline auto keepdims = true;
        NMTOOLS_CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case10)
    {
        inline int shape[3] = {2,3,1};
        inline float result[2][3][1] = {
            {{1}, {3}, { 5}},
            {{7}, {9}, {11}},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case11)
    {
        inline float a[2][3][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
            },
            {
                { 6, 7},
                { 8, 9},
                {10,11},
            },
        };
        inline int axis[2] = {0,1};
        inline auto dtype = None;
        inline auto initial = None;
        inline auto keepdims = false;
        NMTOOLS_CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case11)
    {
        inline int shape[1] = {2};
        inline float result[2] = {10,11};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case12)
    {
        inline float a[2][3][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
            },
            {
                { 6, 7},
                { 8, 9},
                {10,11},
            },
        };
        inline int axis[2] = {0,2};
        inline auto dtype = None;
        inline auto initial = None;
        inline auto keepdims = false;
        NMTOOLS_CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case12)
    {
        inline int shape[1] = {3};
        inline float result[3] = {7,9,11};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case13)
    {
        inline float a[2][3][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
            },
            {
                { 6, 7},
                { 8, 9},
                {10,11},
            },
        };
        inline int axis[2] = {1,2};
        inline auto dtype = None;
        inline auto initial = None;
        inline auto keepdims = true;
        NMTOOLS_CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case13)
    {
        inline int shape[3] = {2,1,1};
        inline float result[2][1][1] = {
            {
                {5}
            },
            {
                {11}
            },
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case14)
    {
        inline float a[2][3][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
            },
            {
                { 6, 7},
                { 8, 9},
                {10,11},
            },
        };
        inline auto axis = nm::None;
        NMTOOLS_CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case14)
    {
        inline auto shape   = nm::None;
        inline float result = 11;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case15)
    {
        inline float a[2][3][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
            },
            {
                { 6, 7},
                { 8, 9},
                {10,11},
            },
        };
        inline auto axis = None;
        inline auto initial = 12;
        inline auto keepdims = False;
        NMTOOLS_CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case15)
    {
        inline auto shape   = nm::None;
        inline float result = 12.0f;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case16)
    {
        inline float a[2][3][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
            },
            {
                { 6, 7},
                { 8, 9},
                {10,11},
            },
        };
        inline auto axis = None;
        inline auto initial = 12;
        inline auto keepdims = True;
        NMTOOLS_CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case16)
    {
        inline int shape[3] = {1,1,1};
        inline float result[1][1][1] = {{{12.0f}}};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case17)
    {
        inline float a[2][3][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
            },
            {
                { 6, 7},
                { 8, 9},
                {10,11},
            },
        };
        inline auto axis = nm::None;
        inline auto initial = 3.0f;
        inline auto keepdims = nm::False;
        NMTOOLS_CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case17)
    {
        inline auto shape   = nm::None;
        inline float result = 11.0f;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case18)
    {
        inline float a[2][3][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
            },
            {
                { 6, 7},
                { 8, 9},
                {10,11},
            },
        };
        inline auto axis = nm::None;
        inline auto initial = 3.0f;
        inline auto keepdims = nm::True;
        NMTOOLS_CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case18)
    {
        inline int shape[3] = {1,1,1};
        inline float result[1][1][1] = {{{11.0f}}};
    }

    // Test cases using 'where' (mask) argument
    NMTOOLS_TESTING_DECLARE_ARGS(case19)
    {
        inline float a[2][3][2] = {
            {{0,1}, {2,3}, {4,5}},
            {{6,7}, {8,9}, {10,11}},
        };
        inline int axis = 0;
        inline auto dtype = nm::None;
        inline auto initial = fmax_initial;
        inline auto keepdims = nm::False;
        inline bool mask[2][3][2] = {
            {{true, false}, {true, true}, {false, true}},
            {{true, true}, {false, false}, {true, true}},
        };
        NMTOOLS_CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case19)
    {
        inline int shape[2] = {3,2};
        inline float result[3][2] = {
            { 6, 7},
            { 2, 3},
            {10,11},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case20)
    {
        inline float a[2][3][2] = {
            {{0,1}, {2,3}, {4,5}},
            {{6,7}, {8,9}, {10,11}},
        };
        inline int axis = 1;
        inline auto dtype = nm::None;
        inline auto initial = -1.0f;
        inline auto keepdims = nm::True;
        inline bool mask[3][2] = {
            {true, false}, {false, true}, {true, true}
        };
        NMTOOLS_CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case20)
    {
        inline int shape[3] = {2,1,2};
        inline float result[2][1][2] = {
            {{4, 5}},
            {{10, 11}},
        };
    }

     NMTOOLS_TESTING_DECLARE_ARGS(case21)
    {
        inline float a[2][3][2] = {
            {{0,1}, {2,3}, {4,5}},
            {{6,7}, {8,9}, {10,11}},
        };
        inline int axis = 2;
        inline auto dtype = nm::None;
        inline auto initial = fmax_initial;
        inline auto keepdims = nm::True;
        inline bool mask[2][3][2] = {
            {{true, true}, {true, false}, {false, true}},
            {{true, false}, {true, true}, {true, false}},
        };
        NMTOOLS_CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case21)
    {
        inline int shape[3] = {2,3,1};
        inline float result[2][3][1] = {
             {{1}, {2}, {5}},
             {{6}, {9}, {10}},
        };
    }


    NMTOOLS_TESTING_DECLARE_ARGS(case22)
    {
        inline float a[2][3][2] = {
            {{0,1}, {2,3}, {4,5}},
            {{6,7}, {8,9}, {10,11}},
        };
        inline int axis[2] = {0,1};
        inline auto dtype = nm::None;
        inline auto initial = fmax_initial;
        inline auto keepdims = nm::False;
        inline bool mask[2][1][2] = {
            {{true, false}},
            {{false, true}},
        };
        NMTOOLS_CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case22)
    {
        inline int shape[1] = {2};
        inline float result[2] = {4, 11};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case23)
    {
        inline float a[2][3][2] = {
            {{0,1}, {2,3}, {4,5}},
            {{6,7}, {8,9}, {10,11}},
        };
        inline int axis = 0;
        inline auto dtype = nm::None;
        inline auto initial = 100.0f;
        inline auto keepdims = nm::False;
        inline bool mask[2][3][2] = {
            {{true, false}, {true, true}, {false, true}},
            {{true, true}, {false, false}, {true, true}},
        };
        NMTOOLS_CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case23)
    {
        inline int shape[2] = {3,2};
        inline float result[3][2] = {
            {100, 100},
            {100, 100},
            {100, 100},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case24)
    {
        inline float a[2][3][2] = {
            {{0,1}, {2,3}, {4,5}},
            {{6,7}, {8,9}, {10,11}},
        };
        inline auto axis = nm::None;
        inline auto dtype = nm::None;
        inline auto initial = fmax_initial;
        inline auto keepdims = nm::False;
        inline bool mask[3][2] = {
            {true, false}, {false, true}, {true, true}
        };
        NMTOOLS_CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case24)
    {
        inline auto shape = nm::None;
        inline float result = 11.0f;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case25)
    {
        inline float a[2][3][2] = {
            {{0,1}, {2,3}, {4,5}},
            {{6,7}, {8,9}, {10,11}},
        };
        inline auto axis = nm::None;
        inline auto dtype = nm::None;
        inline auto initial = fmax_initial;
        inline auto keepdims = nm::True;
        inline bool mask[3][2] = {
            {true, false}, {false, true}, {true, true}
        };
        NMTOOLS_CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case25)
    {
        inline int shape[3] = {1,1,1};
        inline float result[1][1][1] = {{{11.0f}}};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case26)
    {
        inline float a[2][3][2] = {
            {{0,1}, {2,3}, {4,5}},
            {{6,7}, {8,9}, {10,11}},
        };
        inline int axis = 1;
        inline auto dtype = nm::None;
        inline auto initial = 5.5f;
        inline auto keepdims = nm::True;
        inline bool mask[2][1][2] = {
            {{true, false}},
            {{false, true}},
        };
        NMTOOLS_CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case26)
    {
        inline int shape[3] = {2,1,2};
        inline float result[2][1][2] = {
            {{5.5, 5.5}},
            {{5.5, 11.0}},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case27)
    {
        inline float a[2][3][2] = {
            {{0,1}, {2,3}, {4,5}},
            {{6,7}, {8,9}, {10,11}},
        };
        inline auto axis = nm::None;
        inline auto dtype = nm::None;
        inline auto initial = 15.0f;
        inline auto keepdims = nm::True;
        inline bool mask[2][3][2] = {
            {{true, true}, {true, true}, {true, true}},
            {{true, true}, {true, true}, {true, true}},
        };
        NMTOOLS_CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case27)
    {
        inline int shape[3] = {1,1,1};
        inline float result[1][1][1] = {{{15.0f}}};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case28)
    {
        inline float a[2][3][2] = {
            {{0,1}, {2,3}, {4,5}},
            {{6,7}, {8,9}, {10,11}},
        };
        inline auto axis = nm::None;
        inline auto dtype = nm::None;
        inline auto initial = 15.0f;
        inline auto keepdims = nm::False;
        inline bool mask[2][3][2] = {
            {{true, true}, {true, true}, {true, true}},
            {{true, true}, {true, true}, {true, true}},
        };
        NMTOOLS_CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case28)
    {
        inline auto shape = nm::None;
        inline float result = 15.0f;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case29)
    {
        inline float a[2][3][2] = {
            {{0,1}, {2,3}, {4,5}},
            {{6,7}, {8,9}, {10,11}},
        };
        inline int axis[2] = {0, 2};
        inline auto dtype = nm::None;
        inline auto initial = fmax_initial;
        inline auto keepdims = nm::False;
        inline bool mask[2][3][1] = {
            {{true}, {false}, {true}},
            {{false}, {true}, {true}},
        };
        NMTOOLS_CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case29)
    {
        inline int shape[1] = {3};
        inline float result[3] = {1, 9, 11};
    }
}

NMTOOLS_TESTING_DECLARE_CASE(view, accumulate_fmax)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline float a[2][3][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
            },
            {
                { 6, 7},
                { 8, 9},
                {10,11},
            },
        };
        inline int axis = 0;
        NMTOOLS_CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline int shape[3] = {2,3,2};
        inline float result[2][3][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
            },
            {
                { 6, 7},
                { 8, 9},
                {10,11},
            },
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        inline float a[2][3][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
            },
            {
                { 6, 7},
                { 8, 9},
                {10,11},
            },
        };
        inline int axis = 1;
        NMTOOLS_CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        inline int shape[3] = {2,3,2};
        inline float result[2][3][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
            },
            {
                { 6, 7},
                { 8, 9},
                {10,11},
            },
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        inline float a[2][3][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
            },
            {
                { 6, 7},
                { 8, 9},
                {10,11},
            },
        };
        inline int axis = 2;
        NMTOOLS_CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        inline int shape[3] = {2,3,2};
        inline float result[2][3][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
            },
            {
                { 6, 7},
                { 8, 9},
                {10,11},
            },
        };
    }
}

NMTOOLS_TESTING_DECLARE_CASE(view, outer_fmax)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline int a[2][3] = {
            {0,1,2},
            {3,4,5},
        };
        inline int b[3] = { 6,  7, 8};
        NMTOOLS_CAST_ARRAYS(a)
        NMTOOLS_CAST_ARRAYS(b)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline int shape[3] = {2,3,3};
        inline int result[2][3][3] = \
           {{{6, 7, 8},
            {6, 7, 8},
            {6, 7, 8}},
    
           {{6, 7, 8},
            {6, 7, 8},
            {6, 7, 8}}};
    }
}

#endif // NMTOOLS_TESTING_DATA_ARRAY_FMAX_HPP