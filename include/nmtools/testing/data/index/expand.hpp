#ifndef NMTOOLS_TESTING_DATA_INDEX_EXPAND_HPP
#define NMTOOLS_TESTING_DATA_INDEX_EXPAND_HPP

#include "nmtools/testing/testing.hpp"
#include "nmtools/testing/array_cast.hpp"

NMTOOLS_TESTING_DECLARE_CASE(index,shape_expand)
{
    using namespace literals;

    NMTOOLS_TESTING_DECLARE_ARGS(case1)
    {
        inline int src_shape[1] = {6};
        inline auto axis     = 0;
        inline auto spacing = 1;

        inline auto src_shape_ct = nmtools_tuple{6_ct};
        inline auto axis_ct      = 0_ct;
        inline auto spacing_ct  = 1_ct;

        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1)
    {
        inline int result[1] = {11};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2)
    {
        inline int src_shape[1] = {11};
        inline int axis     = -1;
        inline int spacing = 2;

        inline auto src_shape_ct = nmtools_tuple{11_ct};
        inline auto axis_ct      = "-1"_ct;
        inline auto spacing_ct  = 2_ct;

        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2)
    {
        inline int result[1] = {31};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case3)
    {
        inline int src_shape[2] = {5,3};
        inline int axis[2]  = {0,1};
        inline int spacing = 1;

        inline auto src_shape_ct = nmtools_tuple{5_ct,3_ct};
        inline auto axis_ct      = nmtools_tuple{0_ct,1_ct};
        inline auto spacing_ct  = 1_ct;

        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(axis)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case3)
    {
        inline int result[2] = {9,5};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case4)
    {
        inline int src_shape[2] = {5,3};
        inline int axis[2] = {0,1};
        inline int spacing[2] = {1,2};

        inline auto src_shape_ct = nmtools_tuple{5_ct,3_ct};
        inline auto axis_ct      = nmtools_tuple{0_ct,1_ct};
        inline auto spacing_ct  = nmtools_tuple{1_ct,2_ct};

        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(axis)
        NMTOOLS_CAST_INDEX_ARRAYS(spacing)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case4)
    {
        inline int result[2] = {9,7};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case5)
    {
        inline int src_shape[2] = {5,3};
        inline int axis = 0;
        inline int spacing[1] = {1};

        inline auto src_shape_ct = nmtools_tuple{5_ct,3_ct};
        inline auto axis_ct      = 0_ct;
        inline auto spacing_ct  = nmtools_tuple{1_ct};

        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(spacing)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case5)
    {
        inline int result[2] = {9,3};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case6)
    {
        inline int src_shape[2] = {5,3};
        inline int axis[1]      = {-1};
        inline int spacing[1]  = {1};

        inline auto src_shape_ct = nmtools_tuple{5_ct,3_ct};
        inline auto axis_ct      = nmtools_tuple{"-1"_ct};
        inline auto spacing_ct  = nmtools_tuple{1_ct};

        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(axis)
        NMTOOLS_CAST_INDEX_ARRAYS(spacing)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case6)
    {
        inline int result[2] = {5,5};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case7)
    {
        inline int src_shape[3] = {3,2,3};
        inline int axis[3]      = {0,1,2};
        inline int spacing[3]  = {1,1,1};

        inline auto src_shape_ct = nmtools_tuple{3_ct,2_ct,3_ct};
        inline auto axis_ct      = nmtools_tuple{0_ct,1_ct,2_ct};
        inline auto spacing_ct  = nmtools_tuple{1_ct,1_ct,1_ct};

        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
        NMTOOLS_CAST_INDEX_ARRAYS(axis)
        NMTOOLS_CAST_INDEX_ARRAYS(spacing)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case7)
    {
        inline int result[3] = {5,3,5};
    }
}

/*=============================================================*/

NMTOOLS_TESTING_DECLARE_CASE(index,expand)
{
    NMTOOLS_TESTING_DECLARE_ARGS(case1a)
    {
        inline int indices[1] = {0};
        inline int src_shape[1] = {6};
        inline auto axis = 0;
        inline auto spacing = 1;

        NMTOOLS_CAST_INDEX_ARRAYS(indices)
        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1a)
    {
        inline int result[1] = {0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case1b)
    {
        inline int indices[1] = {1};
        inline int src_shape[1] = {6};
        inline auto axis = 0;
        inline auto spacing = 1;

        NMTOOLS_CAST_INDEX_ARRAYS(indices)
        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1b)
    {
        // use None to signal to return 0/fill_value
        inline auto result = None;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case1c)
    {
        inline int indices[1] = {2};
        inline int src_shape[1] = {6};
        inline auto axis = 0;
        inline auto spacing = 1;

        NMTOOLS_CAST_INDEX_ARRAYS(indices)
        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1c)
    {
        inline int result[1] = {1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case1d)
    {
        inline int indices[1] = {3};
        inline int src_shape[1] = {6};
        inline auto axis = 0;
        inline auto spacing = 1;

        NMTOOLS_CAST_INDEX_ARRAYS(indices)
        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1d)
    {
        inline auto result = None;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case1e)
    {
        inline int indices[1] = {4};
        inline int src_shape[1] = {6};
        inline auto axis = 0;
        inline auto spacing = 1;

        NMTOOLS_CAST_INDEX_ARRAYS(indices)
        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1e)
    {
        inline int result[1] = {2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case1f)
    {
        inline int indices[1] = {5};
        inline int src_shape[1] = {6};
        inline auto axis = 0;
        inline auto spacing = 1;

        NMTOOLS_CAST_INDEX_ARRAYS(indices)
        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1f)
    {
        inline auto result = None;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case1g)
    {
        inline int indices[1] = {6};
        inline int src_shape[1] = {6};
        inline auto axis = 0;
        inline auto spacing = 1;

        NMTOOLS_CAST_INDEX_ARRAYS(indices)
        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1g)
    {
        inline int result[1] = {3};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case1h)
    {
        inline int indices[1] = {7};
        inline int src_shape[1] = {6};
        inline auto axis = 0;
        inline auto spacing = 1;

        NMTOOLS_CAST_INDEX_ARRAYS(indices)
        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1h)
    {
        inline auto result = None;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case1i)
    {
        inline int indices[1] = {8};
        inline int src_shape[1] = {6};
        inline auto axis = 0;
        inline auto spacing = 1;

        NMTOOLS_CAST_INDEX_ARRAYS(indices)
        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1i)
    {
        inline int result[1] = {4};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case1j)
    {
        inline int indices[1] = {9};
        inline int src_shape[1] = {6};
        inline auto axis = 0;
        inline auto spacing = 1;

        NMTOOLS_CAST_INDEX_ARRAYS(indices)
        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1j)
    {
        inline auto result = None;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case1k)
    {
        inline int indices[1] = {8};
        inline int src_shape[1] = {6};
        inline auto axis = 0;
        inline auto spacing = 1;

        NMTOOLS_CAST_INDEX_ARRAYS(indices)
        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case1k)
    {
        inline int result[1] = {4};
    }

    /*=============================================================*/

    NMTOOLS_TESTING_DECLARE_ARGS(case2aa)
    {
        inline int indices[2]   = {0,0};
        inline int src_shape[2] = {5,3};
        inline int axis[2]      = {0,1};
        inline int spacing     = 1;

        NMTOOLS_CAST_INDEX_ARRAYS(indices)
        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2aa)
    {
        inline int result[2] = {0,0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2ab)
    {
        inline int indices[2]   = {0,1};
        inline int src_shape[2] = {5,3};
        inline int axis[2]      = {0,1};
        inline int spacing     = 1;

        NMTOOLS_CAST_INDEX_ARRAYS(indices)
        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2ab)
    {
        inline auto result = None;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2ac)
    {
        inline int indices[2]   = {0,2};
        inline int src_shape[2] = {5,3};
        inline int axis[2]      = {0,1};
        inline int spacing     = 1;

        NMTOOLS_CAST_INDEX_ARRAYS(indices)
        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2ac)
    {
        inline int result[2] = {0,1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2ad)
    {
        inline int indices[2]   = {0,3};
        inline int src_shape[2] = {5,3};
        inline int axis[2]      = {0,1};
        inline int spacing     = 1;

        NMTOOLS_CAST_INDEX_ARRAYS(indices)
        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2ad)
    {
        inline auto result = None;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2ae)
    {
        inline int indices[2]   = {0,4};
        inline int src_shape[2] = {5,3};
        inline int axis[2]      = {0,1};
        inline int spacing     = 1;

        NMTOOLS_CAST_INDEX_ARRAYS(indices)
        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2ae)
    {
        inline int result[2] = {0,2};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2ba)
    {
        inline int indices[2]   = {1,0};
        inline int src_shape[2] = {5,3};
        inline int axis[2]      = {0,1};
        inline int spacing     = 1;

        NMTOOLS_CAST_INDEX_ARRAYS(indices)
        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2ba)
    {
        inline auto result = None;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2bb)
    {
        inline int indices[2]   = {1,1};
        inline int src_shape[2] = {5,3};
        inline int axis[2]      = {0,1};
        inline int spacing     = 1;

        NMTOOLS_CAST_INDEX_ARRAYS(indices)
        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2bb)
    {
        inline auto result = None;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2bc)
    {
        inline int indices[2]   = {1,2};
        inline int src_shape[2] = {5,3};
        inline int axis[2]      = {0,1};
        inline int spacing     = 1;

        NMTOOLS_CAST_INDEX_ARRAYS(indices)
        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2bc)
    {
        inline auto result = None;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2ca)
    {
        inline int indices[2]   = {2,0};
        inline int src_shape[2] = {5,3};
        inline int axis[2]      = {0,1};
        inline int spacing     = 1;

        NMTOOLS_CAST_INDEX_ARRAYS(indices)
        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2ca)
    {
        inline int result[2] = {1,0};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2cb)
    {
        inline int indices[2]   = {2,1};
        inline int src_shape[2] = {5,3};
        inline int axis[2]      = {0,1};
        inline int spacing     = 1;

        NMTOOLS_CAST_INDEX_ARRAYS(indices)
        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2cb)
    {
        inline auto result = None;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2cc)
    {
        inline int indices[2]   = {2,2};
        inline int src_shape[2] = {5,3};
        inline int axis[2]      = {0,1};
        inline int spacing     = 1;

        NMTOOLS_CAST_INDEX_ARRAYS(indices)
        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2cc)
    {
        inline int result[2] = {1,1};
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2cd)
    {
        inline int indices[2]   = {2,3};
        inline int src_shape[2] = {5,3};
        inline int axis[2]      = {0,1};
        inline int spacing     = 1;

        NMTOOLS_CAST_INDEX_ARRAYS(indices)
        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2cd)
    {
        inline auto result = None;
    }

    NMTOOLS_TESTING_DECLARE_ARGS(case2ce)
    {
        inline int indices[2]   = {2,4};
        inline int src_shape[2] = {5,3};
        inline int axis[2]      = {0,1};
        inline int spacing     = 1;

        NMTOOLS_CAST_INDEX_ARRAYS(indices)
        NMTOOLS_CAST_INDEX_ARRAYS(src_shape)
    }
    NMTOOLS_TESTING_DECLARE_EXPECT(case2ce)
    {
        inline int result[2] = {1,2};
    }
}

#endif // NMTOOLS_TESTING_DATA_INDEX_EXPAND_HPP