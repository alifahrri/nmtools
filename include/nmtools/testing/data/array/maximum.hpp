#ifndef NMTOOLS_TESTING_DATA_ARRAY_MAXIMUM_HPP
#define NMTOOLS_TESTING_DATA_ARRAY_MAXIMUM_HPP

#include "nmtools/testing/testing.hpp"
#include "nmtools/testing/array_cast.hpp"
#include "nmtools/constants.hpp"
#include "nmtools/meta.hpp"

#include <algorithm> // std::max
#include <limits>    // Required for numeric_limits

namespace nm = nmtools;
namespace na = nm::array;
namespace kind = na::kind;
namespace meta = nm::meta;

constexpr int max_initial = meta::numeric_limits<int>::min();

NMTOOLS_TESTING_DECLARE_CASE(view, maximum)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline int a[3][3] = {
            {0,1,2},
            {3,4,5},
            {6,7,8},
        };
        inline int b[3] = {0,1,2};
        NMTOOLS_CAST_ARRAYS(a)
        NMTOOLS_CAST_ARRAYS(b)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline int shape[2] = {3,3};
        inline int result[3][3] = {
            {std::max(0,0),std::max(1,1),std::max(2,2)},
            {std::max(3,0),std::max(4,1),std::max(5,2)},
            {std::max(6,0),std::max(7,1),std::max(8,2)},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        inline int a[3][3] = {
            {0,1,2},
            {3,4,5},
            {6,7,8},
        };
        inline int b = 2;
        NMTOOLS_CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        inline int shape[2] = {3,3};
        inline int result[3][3] = {
            {std::max(0,2),std::max(1,2),std::max(2,2)},
            {std::max(3,2),std::max(4,2),std::max(5,2)},
            {std::max(6,2),std::max(7,2),std::max(8,2)},
        };
    }
}

NMTOOLS_TESTING_DECLARE_CASE(view, reduce_maximum)
{
    // Existing cases 1-17
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline int a[2][3][2] = {
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
        inline int result[3][2] = {
            { 6, 7},
            { 8, 9},
            {10,11},
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
        inline int result[2][2] = {
            { 4, 5},
            {10,11},
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
        inline int result[2][3] = {
            {1,3, 5},
            {7,9,11},
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
        inline int result[2] = {10,11};
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
        inline int result[3] = {7,9,11};
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
        inline int result[2] = {5,11};
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
        inline int axis[2]  = {1,2};
        inline auto dtype   = int32;
        inline auto initial = 256;
        NMTOOLS_CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case7)
    {
        inline int shape[1] = {2};
        inline int result[2] = {256,256};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case8)
    {
        inline int a[2][3][2] = {
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
        inline int result[1][3][2] = {
            {
                { 6, 7},
                { 8, 9},
                {10,11},
            }
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
        inline int result[2][2] = {
            { 4, 5},
            {10,11},
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
        inline int result[2][3][1] = {
            {{1},{3},{ 5}},
            {{7},{9},{11}},
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
        inline int result[2] = {10,11};
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
                { 6, 7},
                { 8, 9},
                {10,11},
            },
        };
        inline int axis[2] = {0,2};
        inline auto dtype = None;
        inline auto initial = None;
        inline auto keepdims = true;
        NMTOOLS_CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case12)
    {
        inline int shape[3] = {1,3,1};
        inline int result[1][3][1] = {
            {
                {7},
                {9},
                {11}
            }
        };
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
                { 6, 7},
                { 8, 9},
                {10,11},
            },
        };
        inline auto axis = None;
        NMTOOLS_CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case13)
    {
        inline auto shape = None;
        inline int result = 11;
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
    NMTOOLS_TESTING_DECLARE_EXPECT(case14)
    {
        inline auto shape = None;
        inline int result = 12;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case15)
    {
        inline int a[2][3][2] = {
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
    NMTOOLS_TESTING_DECLARE_EXPECT(case15)
    {
        inline int shape[3] = {1,1,1};
        inline int result[1][1][1] = {{{12}}};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case16)
    {
        inline int a[2][3][2] = {
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
        inline auto keepdims = false;
        NMTOOLS_CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case16)
    {
        inline auto shape = None;
        inline int result = 12;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case17)
    {
        inline int a[2][3][2] = {
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
        inline auto keepdims = true;
        NMTOOLS_CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case17)
    {
        inline int shape[3] = {1,1,1};
        inline int result[1][1][1] = {{{12}}};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case18)
    {
        inline int a[2][3][2] = {
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
        inline auto initial = max_initial;
        inline auto keepdims = False;
        inline bool mask[2][3][2] = {
            {{true, false}, {true, true}, {false, true}},
            {{true, true}, {false, false}, {true, true}},
        };
        NMTOOLS_CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case18)
    {
        inline int shape[2] = {3,2};
        inline int result[3][2] = {
            { 6, 7}, { 2, 3}, {10, 11}
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case19)
    {
        inline int a[2][3][2] = {
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
        inline auto initial = -1;
        inline auto keepdims = True;
        inline bool mask[3][2] = {
            {true, false}, {false, true}, {true, true}
        };
        NMTOOLS_CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case19)
    {
        inline int shape[3] = {2,1,2};
        inline int result[2][1][2] = {
            {{4, 5}},
            {{10, 11}},
        };
    }

     NMTOOLS_TESTING_DECLARE_ARGS(case20)
    {
        inline int a[2][3][2] = {
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
        inline auto initial = max_initial;
        inline auto keepdims = True;
        inline bool mask[2][3][2] = {
            {{true, true}, {true, false}, {false, true}},
            {{true, false}, {true, true}, {true, false}},
        };
        NMTOOLS_CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case20)
    {
        inline int shape[3] = {2,3,1};
        inline int result[2][3][1] = {
             {{1}, {2}, {5}},
             {{6}, {9}, {10}},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case21)
    {
        inline int a[2][3][2] = {
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
        inline auto initial = max_initial;
        inline auto keepdims = False;
        inline bool mask[2][1][2] = {
            {{true, false}},
            {{false, true}},
        };
        NMTOOLS_CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case21)
    {
        inline int shape[1] = {2};
        inline int result[2] = {4, 11};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case22)
    {
        inline int a[2][3][2] = {
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
        inline auto initial = 100;
        inline auto keepdims = False;
        inline bool mask[2][3][2] = {
            {{true, false}, {true, true}, {false, true}},
            {{true, true}, {false, false}, {true, true}},
        };
        NMTOOLS_CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case22)
    {
        inline int shape[2] = {3,2};
        inline int result[3][2] = {
            {100, 100}, {100, 100}, {100, 100}
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case23)
    {
        inline int a[2][3][2] = {
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
        inline auto dtype = None;
        inline auto initial = max_initial;
        inline auto keepdims = False;
        inline bool mask[3][2] = {
            {true, false}, {false, true}, {true, true}
        };
        NMTOOLS_CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case23)
    {
        inline auto shape = None;
        inline int result = 11;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case24)
    {
        inline int a[2][3][2] = {
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
        inline auto dtype = None;
        inline auto initial = max_initial;
        inline auto keepdims = True;
        inline bool mask[3][2] = {
            {true, false}, {false, true}, {true, true}
        };
        NMTOOLS_CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case24)
    {
        inline int shape[3] = {1,1,1};
        inline int result[1][1][1] = {{{11}}};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case25)
    {
        inline int a[2][3][2] = {
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
        inline auto initial = 5;
        inline auto keepdims = True;
        inline bool mask[2][1][2] = {
            {{true, false}},
            {{false, true}},
        };
        NMTOOLS_CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case25)
    {
        inline int shape[3] = {2,1,2};
        inline int result[2][1][2] = {
            {{5, 5}},
            {{5, 11}},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case26)
    {
        inline int a[2][3][2] = {
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
        inline auto dtype = None;
        inline auto initial = 15;
        inline auto keepdims = True;
        inline bool mask[2][3][2] = {
            {{true, true}, {true, true}, {true, true}},
            {{true, true}, {true, true}, {true, true}},
        };
        NMTOOLS_CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case26)
    {
        inline int shape[3] = {1,1,1};
        inline int result[1][1][1] = {{{15}}};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case27)
    {
        inline int a[2][3][2] = {
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
        inline auto dtype = None;
        inline auto initial = 15;
        inline auto keepdims = False;
        inline bool mask[2][3][2] = {
            {{true, true}, {true, true}, {true, true}},
            {{true, true}, {true, true}, {true, true}},
        };
        NMTOOLS_CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case27)
    {
        inline auto shape = None;
        inline int result = 15;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case28)
    {
        inline int a[2][3][2] = {
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
        inline int axis[2] = {0, 2};
        inline auto dtype = None;
        inline auto initial = max_initial;
        inline auto keepdims = False;
        inline bool mask[2][3][1] = {
            {{true}, {false}, {true}},
            {{false}, {true}, {true}},
        };
        NMTOOLS_CAST_ARRAYS(a)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case28)
    {
        inline int shape[1] = {3};
        inline int result[3] = {1, 9, 11};
    }
}

NMTOOLS_TESTING_DECLARE_CASE(view, accumulate_maximum)
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
                {0.f,1.f},
                {2.f,3.f},
                {4.f,5.f},
            },
            {
                { 6.f, 7.f},
                { 8.f, 9.f},
                {10.f,11.f},
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
                {0.f,1.f},
                {2.f,3.f},
                {4.f,5.f},
            },
            {
                { 6.f, 7.f},
                { 8.f, 9.f},
                {10.f,11.f},
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
                {0.f,1.f},
                {2.f,3.f},
                {4.f,5.f},
            },
            {
                { 6.f, 7.f},
                { 8.f, 9.f},
                {10.f,11.f},
            },
        };
    }
}

NMTOOLS_TESTING_DECLARE_CASE(view, outer_maximum)
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
        inline int result[2][3][3] = {
           {
               {6, 7, 8},
               {6, 7, 8},
               {6, 7, 8}
           },
           {
               {6, 7, 8},
               {6, 7, 8},
               {6, 7, 8}
           }
        }; // Corrected formatting
    }
}

#endif // NMTOOLS_TESTING_DATA_ARRAY_MAXIMUM_HPP
