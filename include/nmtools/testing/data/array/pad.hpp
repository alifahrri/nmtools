#ifndef NMTOOLS_TESTING_DATA_ARRAY_PAD_HPP
#define NMTOOLS_TESTING_DATA_ARRAY_PAD_HPP

#include "nmtools/testing/testing.hpp"
#include "nmtools/testing/array_cast.hpp"

namespace nm = nmtools;
namespace na = nm::array;
namespace kind = na::kind;

using namespace nm::literals;

NMTOOLS_TESTING_DECLARE_CASE(array, pad)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline int array[3][2] = {
            {0,1},
            {2,3},
            {4,5},
        };
        inline int pads[4] = {0,2,0,0};
        inline int pad[4]  = {2,0,0,0};
        inline int pad_width[2][2] = {
            {0,0},
            {2,0},
        };
        NMTOOLS_CAST_ARRAYS(array);
        NMTOOLS_CAST_INDEX_ARRAYS(pads);
        NMTOOLS_CAST_ARRAYS(pad_width);
        NMTOOLS_CAST_INDEX_ARRAYS(pad);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline int result[3][4] = {
            {0,0,0,1},
            {0,0,2,3},
            {0,0,4,5},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        inline int array[3][2] = {
            {0,1},
            {2,3},
            {4,5},
        };
        inline int pads[4] = {0,2,0,2};
        inline int pad[4]  = {2,2,0,0};
        inline int pad_width[2][2] = {
            {0,0},
            {2,2},
        };
        NMTOOLS_CAST_ARRAYS(array);
        NMTOOLS_CAST_INDEX_ARRAYS(pads);
        NMTOOLS_CAST_ARRAYS(pad_width);
        NMTOOLS_CAST_INDEX_ARRAYS(pad);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        inline int result[3][6] = {
            {0,0,0,1,0,0},
            {0,0,2,3,0,0},
            {0,0,4,5,0,0},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        inline int array[3][2] = {
            {0,1},
            {2,3},
            {4,5},
        };
        inline int pads[4] = {1,2,0,2};
        inline int pad[4]  = {2,2,1,0};
        inline int pad_width[2][2] = {
            {1,0},
            {2,2},
        };
        NMTOOLS_CAST_ARRAYS(array);
        NMTOOLS_CAST_INDEX_ARRAYS(pads);
        NMTOOLS_CAST_ARRAYS(pad_width);
        NMTOOLS_CAST_INDEX_ARRAYS(pad);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        inline int result[4][6] = {
            {0,0,0,0,0,0},
            {0,0,0,1,0,0},
            {0,0,2,3,0,0},
            {0,0,4,5,0,0},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        inline int array[3][2] = {
            {0,1},
            {2,3},
            {4,5},
        };
        inline int pads[4] = {1,2,3,2};
        inline int pad[4]  = {2,2,1,3};
        inline int pad_width[2][2] = {
            {1,3},
            {2,2},
        };
        NMTOOLS_CAST_ARRAYS(array);
        NMTOOLS_CAST_INDEX_ARRAYS(pads);
        NMTOOLS_CAST_ARRAYS(pad_width);
        NMTOOLS_CAST_INDEX_ARRAYS(pad);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        inline int result[7][6] = {
            {0,0,0,0,0,0},
            {0,0,0,1,0,0},
            {0,0,2,3,0,0},
            {0,0,4,5,0,0},
            {0,0,0,0,0,0},
            {0,0,0,0,0,0},
            {0,0,0,0,0,0},
        };
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        inline int array[2][3][2] = {
            {
                {0,1},
                {2,3},
                {4,5},
            },
            {
                { 6, 7},
                { 8, 9},
                {10,11},
            }
        };
        inline int pads[6] = {0,1,1,2,0,1};
        inline int pad[6]  = {1,1,1,0,0,2};
        inline int pad_width[3][2] = {
            {0,2},
            {1,0},
            {1,1},
        };
        NMTOOLS_CAST_ARRAYS(array);
        NMTOOLS_CAST_INDEX_ARRAYS(pads);
        NMTOOLS_CAST_ARRAYS(pad_width);
        NMTOOLS_CAST_INDEX_ARRAYS(pad);
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        inline int result[4][4][4] = {{{ 0,  0,  0,  0},
        { 0,  0,  1,  0},
        { 0,  2,  3,  0},
        { 0,  4,  5,  0}},

       {{ 0,  0,  0,  0},
        { 0,  6,  7,  0},
        { 0,  8,  9,  0},
        { 0, 10, 11,  0}},

       {{ 0,  0,  0,  0},
        { 0,  0,  0,  0},
        { 0,  0,  0,  0},
        { 0,  0,  0,  0}},

       {{ 0,  0,  0,  0},
        { 0,  0,  0,  0},
        { 0,  0,  0,  0},
        { 0,  0,  0,  0}}};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case6)
    {
        // Input array 'b' from numpy: shape(2, 3, 2)
        inline int array[2][3][2] = {
            {
                { 0,  1},
                { 2,  3},
                { 4,  5}
            },
            {
                { 6,  7},
                { 8,  9},
                {10, 11}
            }
        };

        inline int pads[6] = {0,2,4,1,3,5};
        inline int pad[6]  = {4,5,2,3,0,1};

        // pad_width = ((0,1), (2,3), (4,5))
        // Represents padding (before, after) for each dimension
        inline int pad_width[3][2] = {
            {0, 1}, // axis 0
            {2, 3}, // axis 1
            {4, 5}  // axis 2
        };

        // Constant value used for padding (default 0 in numpy)
        // Depending on the nmtools::pad function signature, you might pass this
        // or it might default to 0. Let's define it for clarity.
        inline int constant_value = 0;

        // Cast the arrays for nmtools
        NMTOOLS_CAST_ARRAYS(array);
        NMTOOLS_CAST_ARRAYS(pad_width);
        NMTOOLS_CAST_INDEX_ARRAYS(pads);
        NMTOOLS_CAST_INDEX_ARRAYS(pad);
        // No need to cast a single value like constant_value typically
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case6)
    {
        // Expected output shape: (2+0+1, 3+2+3, 2+4+5) -> (3, 8, 11)
        // Transcribed directly from the numpy 'res' output
        inline int result[3][8][11] = {
        { // Slice 0 (Original Slice 0, padded)
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // Row 0 (Pad Axis1 Before)
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // Row 1 (Pad Axis1 Before)
            {0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0}, // Row 2 (Data[0,0,:], Padded Axis2)
            {0, 0, 0, 0, 2, 3, 0, 0, 0, 0, 0}, // Row 3 (Data[0,1,:], Padded Axis2)
            {0, 0, 0, 0, 4, 5, 0, 0, 0, 0, 0}, // Row 4 (Data[0,2,:], Padded Axis2)
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // Row 5 (Pad Axis1 After)
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // Row 6 (Pad Axis1 After)
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}  // Row 7 (Pad Axis1 After)
        },
        { // Slice 1 (Original Slice 1, padded)
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // Row 0 (Pad Axis1 Before)
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // Row 1 (Pad Axis1 Before)
            {0, 0, 0, 0, 6, 7, 0, 0, 0, 0, 0}, // Row 2 (Data[1,0,:], Padded Axis2)
            {0, 0, 0, 0, 8, 9, 0, 0, 0, 0, 0}, // Row 3 (Data[1,1,:], Padded Axis2)
            {0, 0, 0, 0,10,11, 0, 0, 0, 0, 0}, // Row 4 (Data[1,2,:], Padded Axis2)
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // Row 5 (Pad Axis1 After)
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, // Row 6 (Pad Axis1 After)
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}  // Row 7 (Pad Axis1 After)
        },
        { // Slice 2 (Pad Axis0 After)
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
        }};
    }
}

#endif // NMTOOLS_TESTING_DATA_ARRAY_PAD_HPP