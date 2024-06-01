#ifndef NMTOOLS_TESTING_DATA_INDEX_ROLL_HPP
#define NMTOOLS_TESTING_DATA_INDEX_ROLL_HPP

#include "nmtools/testing/testing.hpp"

NMTOOLS_TESTING_DECLARE_CASE(index, roll)
{
    using namespace literals;

    NMTOOLS_TESTING_DECLARE_ARGS(case1a1)
    {
        inline int shape[1]   = {6};
        inline int indices[1] = {0};
        inline int shift = 1;

        inline auto shape_ct   = nmtools_tuple{6_ct};
        inline auto indices_ct = nmtools_tuple{0_ct};
        inline auto shift_ct = 1_ct;

        NMTOOLS_CAST_INDEX_ARRAYS(shape)
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1a1)
    {
        inline int result[1] = {5};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case1a2)
    {
        inline int shape[1]   = {6};
        inline int indices[1] = {1};
        inline int shift = 1;

        inline auto shape_ct   = nmtools_tuple{6_ct};
        inline auto indices_ct = nmtools_tuple{1_ct};
        inline auto shift_ct = 1_ct;

        NMTOOLS_CAST_INDEX_ARRAYS(shape)
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1a2)
    {
        inline int result[1] = {0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case1a3)
    {
        inline int shape[1]   = {6};
        inline int indices[1] = {2};
        inline int shift = 1;

        inline auto shape_ct   = nmtools_tuple{6_ct};
        inline auto indices_ct = nmtools_tuple{2_ct};
        inline auto shift_ct = 1_ct;

        NMTOOLS_CAST_INDEX_ARRAYS(shape)
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1a3)
    {
        inline int result[1] = {1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case1a4)
    {
        inline int shape[1]   = {6};
        inline int indices[1] = {3};
        inline int shift = 1;

        inline auto shape_ct   = nmtools_tuple{6_ct};
        inline auto indices_ct = nmtools_tuple{3_ct};
        inline auto shift_ct = 1_ct;

        NMTOOLS_CAST_INDEX_ARRAYS(shape)
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1a4)
    {
        inline int result[1] = {2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case1a5)
    {
        inline int shape[1]   = {6};
        inline int indices[1] = {4};
        inline int shift = 1;

        inline auto shape_ct   = nmtools_tuple{6_ct};
        inline auto indices_ct = nmtools_tuple{4_ct};
        inline auto shift_ct = 1_ct;

        NMTOOLS_CAST_INDEX_ARRAYS(shape)
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1a5)
    {
        inline int result[1] = {3};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case1a6)
    {
        inline int shape[1]   = {6};
        inline int indices[1] = {5};
        inline int shift = 1;

        inline auto shape_ct   = nmtools_tuple{6_ct};
        inline auto indices_ct = nmtools_tuple{5_ct};
        inline auto shift_ct = 1_ct;

        NMTOOLS_CAST_INDEX_ARRAYS(shape)
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1a6)
    {
        inline int result[1] = {4};
    }

    /*===============================================================*/

    NMTOOLS_TESTING_DECLARE_ARGS(case1b1)
    {
        inline int shape[1]   = {6};
        inline int indices[1] = {0};
        inline int shift = 2;

        inline auto shape_ct   = nmtools_tuple{6_ct};
        inline auto indices_ct = nmtools_tuple{0_ct};
        inline auto shift_ct = 2_ct;

        NMTOOLS_CAST_INDEX_ARRAYS(shape)
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1b1)
    {
        inline int result[1] = {4};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case1b2)
    {
        inline int shape[1]   = {6};
        inline int indices[1] = {1};
        inline int shift = 2;

        inline auto shape_ct   = nmtools_tuple{6_ct};
        inline auto indices_ct = nmtools_tuple{1_ct};
        inline auto shift_ct = 2_ct;

        NMTOOLS_CAST_INDEX_ARRAYS(shape)
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1b2)
    {
        inline int result[1] = {5};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case1b3)
    {
        inline int shape[1]   = {6};
        inline int indices[1] = {2};
        inline int shift = 2;

        inline auto shape_ct   = nmtools_tuple{6_ct};
        inline auto indices_ct = nmtools_tuple{2_ct};
        inline auto shift_ct = 2_ct;

        NMTOOLS_CAST_INDEX_ARRAYS(shape)
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1b3)
    {
        inline int result[1] = {0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case1b4)
    {
        inline int shape[1]   = {6};
        inline int indices[1] = {3};
        inline int shift = 2;

        inline auto shape_ct   = nmtools_tuple{6_ct};
        inline auto indices_ct = nmtools_tuple{3_ct};
        inline auto shift_ct = 2_ct;

        NMTOOLS_CAST_INDEX_ARRAYS(shape)
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1b4)
    {
        inline int result[1] = {1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case1b5)
    {
        inline int shape[1]   = {6};
        inline int indices[1] = {4};
        inline int shift = 2;

        inline auto shape_ct   = nmtools_tuple{6_ct};
        inline auto indices_ct = nmtools_tuple{4_ct};
        inline auto shift_ct = 2_ct;

        NMTOOLS_CAST_INDEX_ARRAYS(shape)
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1b5)
    {
        inline int result[1] = {2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case1b6)
    {
        inline int shape[1]   = {6};
        inline int indices[1] = {5};
        inline int shift = 2;

        inline auto shape_ct   = nmtools_tuple{6_ct};
        inline auto indices_ct = nmtools_tuple{5_ct};
        inline auto shift_ct = 2_ct;

        NMTOOLS_CAST_INDEX_ARRAYS(shape)
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1b6)
    {
        inline int result[1] = {3};
    }

    /*===============================================================*/

    NMTOOLS_TESTING_DECLARE_ARGS(case1c1)
    {
        inline int shape[1]   = {6};
        inline int indices[1] = {0};
        inline int shift = -2;

        inline auto shape_ct   = nmtools_tuple{6_ct};
        inline auto indices_ct = nmtools_tuple{0_ct};
        inline auto shift_ct = "-2"_ct;

        NMTOOLS_CAST_INDEX_ARRAYS(shape)
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1c1)
    {
        inline int result[1] = {2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case1c2)
    {
        inline int shape[1]   = {6};
        inline int indices[1] = {1};
        inline int shift = -2;

        inline auto shape_ct   = nmtools_tuple{6_ct};
        inline auto indices_ct = nmtools_tuple{1_ct};
        inline auto shift_ct = "-2"_ct;

        NMTOOLS_CAST_INDEX_ARRAYS(shape)
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1c2)
    {
        inline int result[1] = {3};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case1c3)
    {
        inline int shape[1]   = {6};
        inline int indices[1] = {2};
        inline int shift = -2;

        inline auto shape_ct   = nmtools_tuple{6_ct};
        inline auto indices_ct = nmtools_tuple{2_ct};
        inline auto shift_ct = "-2"_ct;

        NMTOOLS_CAST_INDEX_ARRAYS(shape)
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1c3)
    {
        inline int result[1] = {4};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case1c4)
    {
        inline int shape[1]   = {6};
        inline int indices[1] = {3};
        inline int shift = -2;

        inline auto shape_ct   = nmtools_tuple{6_ct};
        inline auto indices_ct = nmtools_tuple{3_ct};
        inline auto shift_ct = "-2"_ct;

        NMTOOLS_CAST_INDEX_ARRAYS(shape)
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1c4)
    {
        inline int result[1] = {5};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case1c5)
    {
        inline int shape[1]   = {6};
        inline int indices[1] = {4};
        inline int shift = -2;

        inline auto shape_ct   = nmtools_tuple{6_ct};
        inline auto indices_ct = nmtools_tuple{4_ct};
        inline auto shift_ct = "-2"_ct;

        NMTOOLS_CAST_INDEX_ARRAYS(shape)
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1c5)
    {
        inline int result[1] = {0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case1c6)
    {
        inline int shape[1]   = {6};
        inline int indices[1] = {5};
        inline int shift = -2;

        inline auto shape_ct   = nmtools_tuple{6_ct};
        inline auto indices_ct = nmtools_tuple{5_ct};
        inline auto shift_ct = "-2"_ct;

        NMTOOLS_CAST_INDEX_ARRAYS(shape)
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1c6)
    {
        inline int result[1] = {1};
    }

    /*===============================================================*/

    NMTOOLS_TESTING_DECLARE_ARGS(case2c1)
    {
        inline int shape[2]   = {2,4};
        inline int indices[2] = {0,0};
        inline int shift = 1;
        inline int axis  = 0;

        inline auto shape_ct   = nmtools_tuple{2_ct,4_ct};
        inline auto indices_ct = nmtools_tuple{0_ct,0_ct};
        inline auto shift_ct = 1_ct;
        inline auto axis_ct  = 0_ct;

        NMTOOLS_CAST_INDEX_ARRAYS(shape)
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2c1)
    {
        inline int result[2] = {1,0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2c2)
    {
        inline int shape[2]   = {2,4};
        inline int indices[2] = {0,1};
        inline int shift = 1;
        inline int axis  = 0;

        inline auto shape_ct   = nmtools_tuple{2_ct,4_ct};
        inline auto indices_ct = nmtools_tuple{0_ct,1_ct};
        inline auto shift_ct = 1_ct;
        inline auto axis_ct  = 0_ct;

        NMTOOLS_CAST_INDEX_ARRAYS(shape)
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2c2)
    {
        inline int result[2] = {1,1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2c3)
    {
        inline int shape[2]   = {2,4};
        inline int indices[2] = {0,2};
        inline int shift = 1;
        inline int axis  = 0;

        inline auto shape_ct   = nmtools_tuple{2_ct,4_ct};
        inline auto indices_ct = nmtools_tuple{0_ct,2_ct};
        inline auto shift_ct = 1_ct;
        inline auto axis_ct  = 0_ct;

        NMTOOLS_CAST_INDEX_ARRAYS(shape)
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2c3)
    {
        inline int result[2] = {1,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2c4)
    {
        inline int shape[2]   = {2,4};
        inline int indices[2] = {0,3};
        inline int shift = 1;
        inline int axis  = 0;

        inline auto shape_ct   = nmtools_tuple{2_ct,4_ct};
        inline auto indices_ct = nmtools_tuple{0_ct,3_ct};
        inline auto shift_ct = 1_ct;
        inline auto axis_ct  = 0_ct;

        NMTOOLS_CAST_INDEX_ARRAYS(shape)
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2c4)
    {
        inline int result[2] = {1,3};
    }

    /*===============================================================*/

    NMTOOLS_TESTING_DECLARE_ARGS(case2d1)
    {
        inline int shape[2]   = {2,4};
        inline int indices[2] = {0,0};
        inline int shift   = 1;
        inline int axis[2] = {1,0};

        inline auto shape_ct   = nmtools_tuple{2_ct,4_ct};
        inline auto indices_ct = nmtools_tuple{0_ct,0_ct};
        inline auto shift_ct = 1_ct;
        inline auto axis_ct  = nmtools_tuple{1_ct,0_ct};

        NMTOOLS_CAST_INDEX_ARRAYS(shape)
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2d1)
    {
        inline int result[2] = {1,3};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2d2)
    {
        inline int shape[2]   = {2,4};
        inline int indices[2] = {0,1};
        inline int shift   = 1;
        inline int axis[2] = {1,0};

        inline auto shape_ct   = nmtools_tuple{2_ct,4_ct};
        inline auto indices_ct = nmtools_tuple{0_ct,1_ct};
        inline auto shift_ct = 1_ct;
        inline auto axis_ct  = nmtools_tuple{1_ct,0_ct};

        NMTOOLS_CAST_INDEX_ARRAYS(shape)
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2d2)
    {
        inline int result[2] = {1,0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2d3)
    {
        inline int shape[2]   = {2,4};
        inline int indices[2] = {0,2};
        inline int shift   = 1;
        inline int axis[2] = {1,0};

        inline auto shape_ct   = nmtools_tuple{2_ct,4_ct};
        inline auto indices_ct = nmtools_tuple{0_ct,2_ct};
        inline auto shift_ct = 1_ct;
        inline auto axis_ct  = nmtools_tuple{1_ct,0_ct};

        NMTOOLS_CAST_INDEX_ARRAYS(shape)
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2d3)
    {
        inline int result[2] = {1,1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2d4)
    {
        inline int shape[2]   = {2,4};
        inline int indices[2] = {0,3};
        inline int shift   = 1;
        inline int axis[2] = {1,0};

        inline auto shape_ct   = nmtools_tuple{2_ct,4_ct};
        inline auto indices_ct = nmtools_tuple{0_ct,3_ct};
        inline auto shift_ct = 1_ct;
        inline auto axis_ct  = nmtools_tuple{1_ct,0_ct};

        NMTOOLS_CAST_INDEX_ARRAYS(shape)
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2d4)
    {
        inline int result[2] = {1,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2d5)
    {
        inline int shape[2]   = {2,4};
        inline int indices[2] = {1,0};
        inline int shift   = 1;
        inline int axis[2] = {1,0};

        inline auto shape_ct   = nmtools_tuple{2_ct,4_ct};
        inline auto indices_ct = nmtools_tuple{1_ct,0_ct};
        inline auto shift_ct = 1_ct;
        inline auto axis_ct  = nmtools_tuple{1_ct,0_ct};

        NMTOOLS_CAST_INDEX_ARRAYS(shape)
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2d5)
    {
        inline int result[2] = {0,3};
    }

    /*===============================================================*/

    NMTOOLS_TESTING_DECLARE_ARGS(case2e1)
    {
        inline int shape[2]   = {2,4};
        inline int indices[2] = {0,0};
        inline int shift[2]   = {1,2};
        inline int axis[2]    = {0,1};

        inline auto shape_ct   = nmtools_tuple{2_ct,4_ct};
        inline auto indices_ct = nmtools_tuple{0_ct,0_ct};
        inline auto shift_ct   = nmtools_tuple{1_ct,2_ct};
        inline auto axis_ct    = nmtools_tuple{0_ct,1_ct};

        NMTOOLS_CAST_INDEX_ARRAYS(shape)
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2e1)
    {
        inline int result[2] = {1,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2e2)
    {
        inline int shape[2]   = {2,4};
        inline int indices[2] = {0,1};
        inline int shift[2]   = {1,2};
        inline int axis[2]    = {0,1};

        inline auto shape_ct   = nmtools_tuple{2_ct,4_ct};
        inline auto indices_ct = nmtools_tuple{0_ct,1_ct};
        inline auto shift_ct   = nmtools_tuple{1_ct,2_ct};
        inline auto axis_ct    = nmtools_tuple{0_ct,1_ct};

        NMTOOLS_CAST_INDEX_ARRAYS(shape)
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2e2)
    {
        inline int result[2] = {1,3};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2e3)
    {
        inline int shape[2]   = {2,4};
        inline int indices[2] = {1,0};
        inline int shift[2]   = {1,2};
        inline int axis[2]    = {0,1};

        inline auto shape_ct   = nmtools_tuple{2_ct,4_ct};
        inline auto indices_ct = nmtools_tuple{1_ct,0_ct};
        inline auto shift_ct   = nmtools_tuple{1_ct,2_ct};
        inline auto axis_ct    = nmtools_tuple{0_ct,1_ct};

        NMTOOLS_CAST_INDEX_ARRAYS(shape)
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2e3)
    {
        inline int result[2] = {0,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2e4)
    {
        inline int shape[2]   = {2,4};
        inline int indices[2] = {1,2};
        inline int shift[2]   = {1,2};
        inline int axis[2]    = {0,1};

        inline auto shape_ct   = nmtools_tuple{2_ct,4_ct};
        inline auto indices_ct = nmtools_tuple{1_ct,2_ct};
        inline auto shift_ct   = nmtools_tuple{1_ct,2_ct};
        inline auto axis_ct    = nmtools_tuple{0_ct,1_ct};

        NMTOOLS_CAST_INDEX_ARRAYS(shape)
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2e4)
    {
        inline int result[2] = {0,0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2e5)
    {
        inline int shape[2]   = {2,4};
        inline int indices[2] = {1,3};
        inline int shift[2]   = {1,2};
        inline int axis[2]    = {0,1};

        inline auto shape_ct   = nmtools_tuple{2_ct,4_ct};
        inline auto indices_ct = nmtools_tuple{1_ct,3_ct};
        inline auto shift_ct   = nmtools_tuple{1_ct,2_ct};
        inline auto axis_ct    = nmtools_tuple{0_ct,1_ct};

        NMTOOLS_CAST_INDEX_ARRAYS(shape)
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2e5)
    {
        inline int result[2] = {0,1};
    }

    /*===============================================================*/

    NMTOOLS_TESTING_DECLARE_ARGS(case3b1)
    {
        inline int shape[3]   = {2,3,2};
        inline int indices[3] = {0,0,0};
        inline int shift = 1;
        inline int axis  = 0;

        inline auto shape_ct   = nmtools_tuple{2_ct,3_ct,2_ct};
        inline auto indices_ct = nmtools_tuple{0_ct,0_ct,0_ct};
        inline auto shift_ct = 1_ct;
        inline auto axis_ct  = 0_ct;

        NMTOOLS_CAST_INDEX_ARRAYS(shape)
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3b1)
    {
        inline int result[3] = {1,0,0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3b2)
    {
        inline int shape[3]   = {2,3,2};
        inline int indices[3] = {0,0,1};
        inline int shift = 1;
        inline int axis  = 0;

        inline auto shape_ct   = nmtools_tuple{2_ct,3_ct,2_ct};
        inline auto indices_ct = nmtools_tuple{0_ct,0_ct,1_ct};
        inline auto shift_ct = 1_ct;
        inline auto axis_ct  = 0_ct;

        NMTOOLS_CAST_INDEX_ARRAYS(shape)
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3b2)
    {
        inline int result[3] = {1,0,1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3b3)
    {
        inline int shape[3]   = {2,3,2};
        inline int indices[3] = {0,2,0};
        inline int shift = 1;
        inline int axis  = 0;

        inline auto shape_ct   = nmtools_tuple{2_ct,3_ct,2_ct};
        inline auto indices_ct = nmtools_tuple{0_ct,2_ct,0_ct};
        inline auto shift_ct = 1_ct;
        inline auto axis_ct  = 0_ct;

        NMTOOLS_CAST_INDEX_ARRAYS(shape)
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3b3)
    {
        inline int result[3] = {1,2,0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3b4)
    {
        inline int shape[3]   = {2,3,2};
        inline int indices[3] = {1,0,0};
        inline int shift = 1;
        inline int axis  = 0;

        inline auto shape_ct   = nmtools_tuple{2_ct,3_ct,2_ct};
        inline auto indices_ct = nmtools_tuple{1_ct,0_ct,0_ct};
        inline auto shift_ct = 1_ct;
        inline auto axis_ct  = 0_ct;

        NMTOOLS_CAST_INDEX_ARRAYS(shape)
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3b4)
    {
        inline int result[3] = {0,0,0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3b5)
    {
        inline int shape[3]   = {2,3,2};
        inline int indices[3] = {1,1,1};
        inline int shift = 1;
        inline int axis  = 0;

        inline auto shape_ct   = nmtools_tuple{2_ct,3_ct,2_ct};
        inline auto indices_ct = nmtools_tuple{1_ct,1_ct,1_ct};
        inline auto shift_ct = 1_ct;
        inline auto axis_ct  = 0_ct;

        NMTOOLS_CAST_INDEX_ARRAYS(shape)
        NMTOOLS_CAST_INDEX_ARRAYS(indices)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3b5)
    {
        inline int result[3] = {0,1,1};
    }
}

#endif // NMTOOLS_TESTING_DATA_INDEX_ROLL_HPP